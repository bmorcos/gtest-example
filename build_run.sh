#!/bin/bash
# This will build the test suites, run the executables, and gather coverage info
#
# USAGE:
# Running with no args will build all the tests, run them, and print a summary
# including code coverage:
#
#   ./build_run.sh
#
# If you include the "-report" flag, human readable lcov summaries will be
# generated and dropped in the BUILD_DIR named "<exe name>-html":
#
#   ./build_run.sh -report
#
# If you include the "-clean" flag, the build directory is removed and nothing
# else is done, regardless of other flags.
#
#   ./build_run.sh -clean

# Parse arguments
for opt in "$@"; do
    case $opt in
        -report)
            REPORT=1
            shift  # Next arg
        ;;
        -clean)
            CLEAN=1
            shift  # Next arg
        ;;
    esac
done


BUILD_DIR="_build"

# Output colour codes
NC="\033[0m"          # Normal
CYAN_B="\033[1;36m"   # Bold cyan
RED_B="\033[1;31m"    # Bold red
GREEN_B="\033[1;32m"  # Bold green

# Create array of executable names to store functional results
declare -A EXE
EXE[runSimpleTests]=0
EXE[runFailingTests]=0
EXE[runFixtureTests]=0
EXE[runParamTests]=0

# Create array of executable names to store code coverage results
declare -A COV
COV[runSimpleTests]=0
COV[runFailingTests]=0
COV[runFixtureTests]=0
COV[runParamTests]=0

FAIL=0          # Flag if anything fails
COV_THRESH=100  # Min threshold for code coverage
PREFIX=" >>"    # Prefix for printing status in summary

# Clean case, don't do anything else
if [[ -n $CLEAN ]]; then
    echo -e "${CYAN_B}Cleaning build dir...${NC}"
    rm -rf $BUILD_DIR
    exit
fi

# Create test dir and move there to keep source dir clean
mkdir -p $BUILD_DIR
cd $BUILD_DIR || exit

# Build tests
cmake ..
make || exit

# Run tests
for test in "${!EXE[@]}"; do
    echo -e "\n${CYAN_B}Running $test...${NC}"
    ./$test || EXE[$test]=1
done

# Grab code coverage
for test in "${!COV[@]}"; do
    cd CMakeFiles/${test}.dir/code/src || exit  # Move into object dir
    # Run gcov to print summary to stdout, use awk to extract coverage percent
    COV[$test]=$(gcov ./*.gcno | \
                 awk '/easy_math.cpp/{getline; print $2;}' | \
                 awk -F ':' '{print $2}' | tr -d %)
    cd ../../../.. || exit  # Back up to test dir
done

# Print test summary
for test in "${!EXE[@]}"; do
    echo -e "${CYAN_B}$test${NC}"

    echo -n "$PREFIX Functional: "
    # Grab functional status
    if [ "${EXE[$test]}" -eq "0" ]; then
        echo -e "${GREEN_B}PASS${NC}"
    else
        echo -e "${RED_B}FAIL${NC}"
        FAIL=1
    fi

    # Grab coverage status (potentially over multiple files)
    for val in ${COV[$test]}; do
        echo -n "$PREFIX Coverage: "
        if (( $(echo "$val >= $COV_THRESH" |bc -l) )); then
            echo -e "${GREEN_B}$val${NC}"
        else
            echo -e "${RED_B}$val${NC}"
            FAIL=1
        fi
    done
done

# Generate HTML reports if flag given
if [[ -n $REPORT ]]; then
        echo -e "\n${CYAN_B}Generating HTML reports...${NC}"
    for test in "${!COV[@]}"; do
        echo "$PREFIX $test"
        cd CMakeFiles/${test}.dir/code/src || exit  # Move into object dir
        # gcov will have already run, just grab info for lcov
        lcov --capture --directory . --output-file "$test".info > /dev/null
        genhtml "$test".info --output-directory ../../../../"$test"-html > /dev/null
        cd ../../../.. || exit  # Back up to test dir
    done
fi

exit "$FAIL"

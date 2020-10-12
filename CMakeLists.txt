cmake_minimum_required(VERSION 3.1)

## Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})  # Var managed by CMake

## Add GTest required libraries to linker
link_libraries(${GTEST_LIBRARIES} gtest_main pthread)

## Set c++ 11 std
set(CMAKE_CXX_STANDARD 11)

## Include our source directories
set(CMAKE_INCLUDE_CURRENT_DIR True)

## Set gcov flags
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov")

## Define executables for each test suite
set(SIMPLE "runSimpleTests")
add_executable(${SIMPLE} "test/src/simple_tests.cpp" "code/src/easy_math.cpp")

set(FAILING "runFailingTests")
add_executable(${FAILING} "test/src/failing_tests.cpp" "code/src/easy_math.cpp")

set(FIXTURE "runFixtureTests")
add_executable(${FIXTURE} "test/src/fixture_tests.cpp" "code/src/easy_math.cpp")

set(PARAM "runParamTests")
add_executable(${PARAM} "test/src/parametric_tests.cpp" "code/src/easy_math.cpp")

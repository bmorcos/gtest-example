cmake_minimum_required(VERSION 3.1)

## Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})  # Var managed by CMake

## Set c++ 11 std
set(CMAKE_CXX_STANDARD 11)

## Include our source directories
set(CMAKE_INCLUDE_CURRENT_DIR True)

## Define executables for each test suite
set(SIMPLE "runSimpleTests")
add_executable(${SIMPLE} "test/src/simple_tests.cpp")
target_link_libraries(${SIMPLE} ${GTEST_LIBRARIES} gtest_main pthread)

set(FAILING "runFailingTests")
add_executable(${FAILING} "test/src/failing_tests.cpp")
target_link_libraries(${FAILING} ${GTEST_LIBRARIES} gtest_main pthread)

set(FIXTURE "runFixtureTests")
add_executable(${FIXTURE} "test/src/fixture_tests.cpp")
target_link_libraries(${FIXTURE} ${GTEST_LIBRARIES} gtest_main pthread)

set(PARAM "runParamTests")
add_executable(${PARAM} "test/src/parametric_tests.cpp")
target_link_libraries(${PARAM} ${GTEST_LIBRARIES} gtest_main pthread)

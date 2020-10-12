// Fixtured test cases
#ifndef TEST_INC_FIXTURE_TESTS_H_
#define TEST_INC_FIXTURE_TESTS_H_

#include <iostream>
#include "test/inc/common.h"

using ::testing::Test;  // GTest test fixture

/* Inherit GTest base test fixture and create our own fixture
 *****************************************************************************/
class MathsTest : public Test {
 protected:
  // Declare some member variables local to each test case
  int counter;
  float a, b;
  EasyMaths* maths;

  // GTest runs this before any test code
  void SetUp() override {
    std::cout << NOTE_PREFIX << "Fixture SetUp..." << std::endl;
    counter = 0;
    a = 5.;
    b = 2.;
    maths = new EasyMaths(a, b, &counter);
  }

  // GTest runs after all test code
  void TearDown() override {
    delete maths;
    std::cout << NOTE_PREFIX << "Fixture TearDown..." << std::endl;
  }
};

#endif  // TEST_INC_FIXTURE_TESTS_H_

// Parametric test cases
#ifndef TEST_INC_PARAMETRIC_TESTS_H_
#define TEST_INC_PARAMETRIC_TESTS_H_

#include <iostream>
#include <tuple>
#include "test/inc/common.h"

using ::testing::TestWithParam;  // GTest parametric test fixture

/* Inherit GTest parametric test fixture
 *
 * For a single parameter you do not need std::tuple, this is just used to
 * insert multiple values into the single parameter slot.
 *
 * Params: a, b
 *****************************************************************************/
class SweepTest : public TestWithParam<std::tuple<float, float>> {
 protected:
  // Declare some member variables local to each test case
  int counter;
  float a, b;
  EasyMaths* maths;

  // GTest runs this before any test code
  void SetUp() override {
    counter = 0;

    // `GetParam()` fetches the parameter, then we unpack the tuple
    a = std::get<0>(GetParam());
    b = std::get<1>(GetParam());
    maths = new EasyMaths(a, b, &counter);
  }

  // GTest runs after all test code
  void TearDown() override { delete maths; }
};

#endif  // TEST_INC_PARAMETRIC_TESTS_H_

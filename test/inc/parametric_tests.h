// Parametric test cases
#ifndef TEST_INC_FIXTURE_TESTS_H_
#define TEST_INC_FIXTURE_TESTS_H_

#include <tuple>
#include <iostream>
#include "test/inc/common.h"

typedef float DTYPE;

using ::testing::TestWithParam;  // GTest parametric test fixture

/* Inherit GTest parametric test fixture
 *
 * For a single parameter you do not need std::tuple, this is just used to
 * insert multiple values into the single parameter slot.
 *
 * Params: a, b
 *****************************************************************************/
class SweepTest : public TestWithParam<std::tuple<DTYPE, DTYPE>> {
 protected:
  // Declare some member variables local to each test case
  int counter;
  DTYPE a, b;
  EasyMaths<DTYPE>* maths;

  // GTest runs this before any test code
  void SetUp() override {
    counter = 0;

    // `GetParam()` fetches the parameter, then we unpack the tuple
    a = std::get<0>(GetParam());
    b = std::get<1>(GetParam());
    maths = new EasyMaths<DTYPE>(a, b, &counter);
  }

  // GTest runs after all test code
  void TearDown() override {
    delete maths;
  }
};

#endif  // TEST_INC_FIXTURE_TESTS_H_

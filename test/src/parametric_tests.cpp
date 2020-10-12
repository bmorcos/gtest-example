// Parametric test cases
#include "test/inc/parametric_tests.h"

// GTest param generators so we don't have to write the namespace everywhere
using ::testing::Combine;
using ::testing::Values;

/* TEST_P pulls the parametric fixture of the same name from the header.
 * A list of parameters is later instantiated for *all* tests in the suite
 * (i.e. tests that are using this parametric fixture)
 *****************************************************************************/

/* Test the `add` method with various values
 *****************************************************************************/
TEST_P(SweepTest, TestAdd) {
  float result;
  result = maths->add();

  float expected = a + b;

  // Notice the 'FLOAT' designation in our check
  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to add numbers correctly!";
}

/* Test the `mult` method with various values
 *****************************************************************************/
TEST_P(SweepTest, TestMult) {
  float result;
  result = maths->mult();

  float expected = a * b;

  // Notice the 'FLOAT' designation in our check
  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to multiply numbers correctly!";
}

/* Define the parameter sets
 *
 * The parameter sets are run for all test cases in the test suite
 * (e.g. SweepTest in this case)
 *****************************************************************************/
// Explicitly list test cases using `Values`. This is 2 sets of params
INSTANTIATE_TEST_CASE_P(SelectValues, SweepTest,
                        Values(std::tuple<float, float>{1., 2.},
                               std::tuple<float, float>{-1., -2.}));

// Use `Combine` to generate all param combinations. This is 9 sets of params
INSTANTIATE_TEST_CASE_P(ComboValues, SweepTest,
                        Combine(Values(-1., 1., 2.5),  // values for `a`
                                Values(-2., 2, 5.)));  // values for `b`

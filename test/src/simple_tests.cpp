// Simple test case
#include "test/inc/common.h"

/* `TEST` is the base test type with no extra setup, tear down, or
 * additional infrastructure; the entire test case is defined here.
 * You can still have multiple simple tests in a single test suite
 * (e.g. SimpleTests).
 *****************************************************************************/

/* Test the EasyMaths constructor correctly sets an external instance counter
 *****************************************************************************/
TEST(SimpleTests, TestConstructor) {
  int n_instances = 0;

  // We expect our class constructor to increment the n_instances counter
  EasyMaths maths0(1, 1, &n_instances);
  EXPECT_EQ(1, n_instances) << ERR_PREFIX
                            << "Constructor failed to increment counter!";

  // Try a second instance to see if it holds up
  EasyMaths maths1(1, 1, &n_instances);
  EXPECT_EQ(2, n_instances) << ERR_PREFIX
                            << "Constructor failed to increment counter!";
}

/* Test the EasyMaths destructor correctly sets an external instance counter
 *****************************************************************************/
TEST(SimpleTests, TestDestructor) {
  int n_instances;

  EasyMaths maths0(1, 1, &n_instances);
  EasyMaths maths1(1, 1, &n_instances);
  n_instances = 2;  // Set expectation so we don't rely on constructor

  // Check if the destructor decrements the counter
  maths0.~EasyMaths();
  maths1.~EasyMaths();
  EXPECT_EQ(0, n_instances) << ERR_PREFIX
                            << "Destructor failed to decrement counter!";
}

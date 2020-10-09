// Tests meant to fail
#include <iostream>
#include "test/inc/common.h"

/* Demonstrate non-fatal failure
 *
 * Using the EXPECT_* test functions allows the test case to continue
 * despite a failure
 *****************************************************************************/
TEST(FailingTests, TestNonFatal) {
  bool pass = false;
  EXPECT_TRUE(pass) << ERR_PREFIX << "Expected non-fatal failure!";
  std::cout << NOTE_PREFIX << "This line is still executed!" << std::endl;
}

/* Demonstrate fatal failure
 *
 * Using the ASSERT_* test functions immediately abandons the test case
 *****************************************************************************/
TEST(FailingTests, TestFatal) {
  bool pass = false;
  ASSERT_TRUE(pass) << ERR_PREFIX << "Expected fatal failure!";
  std::cout << NOTE_PREFIX << "This line will not be executed!" << std::endl;
}


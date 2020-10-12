// Fixtured test cases
#include "test/inc/fixture_tests.h"

/* TEST_F pulls the fixture of the same name from the header.
 * The fixture in the header defines some local test variables and
 * can run some SetUp and TearDown code surrounding each test case.
 * There are print statements in the fixture SetUp, the test case, and
 * the fixture TearDown to illustrate this point.
 *****************************************************************************/

/* Test the `add` method
 *****************************************************************************/
TEST_F(MathsTest, TestAdd) {
  std::cout << NOTE_PREFIX << "Testing..." << std::endl;

  float result;
  result = maths->add();

  float expected = a + b;

  // Notice the 'FLOAT' designation in our check
  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to add numbers correctly!";
}

/* Test the `mult` method
 *****************************************************************************/
TEST_F(MathsTest, TestMult) {
  std::cout << NOTE_PREFIX << "Testing..." << std::endl;

  float result;
  result = maths->mult();

  float expected = a * b;

  // Notice the 'FLOAT' designation in our check
  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to multiply numbers correctly!";
}

/* Test the `sub` method
 *****************************************************************************/
TEST_F(MathsTest, TestSub) {
  std::cout << NOTE_PREFIX << "Testing..." << std::endl;

  float result;
  result = maths->sub();

  float expected = a - b;

  // Notice the 'FLOAT' designation in our check
  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to subtract numbers correctly!";
}

/* Test the `div` method
 *****************************************************************************/
TEST_F(MathsTest, TestDiv) {
  std::cout << NOTE_PREFIX << "Testing..." << std::endl;

  float result;
  result = maths->div();

  float expected = a / b;

  // Notice the 'FLOAT' designation in our check
  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to divide numbers correctly!";
}

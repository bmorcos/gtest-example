# GTest Example Repo

This is a simple example repo illustrating how to use GTest to test C++ code. As
a demonstration I use a simple class that holds two values and can perform
addition, multiplication, subtraction, and division of said values.

TODO:
- A little info about GTest
- Point to GTest resources
- Not an exhaustive demo, e.g. global setup/teardown


## Requirements

This has been developed and tested under Ubuntu 16.04 and the instructions are
for the same, it's possible you may need to slightly modify commands for your
setup.


### GCC

We use GCC (specifically ``g++``) to build the C source code. This is likely
already installed, but if not it is easy to install with ``sudo apt install
g++``.


### CMake

We use ``cmake`` to facilitate building the test suites. We don't need the very
latest version so you can simply install with ``sudo apt install cmake``.


### GTest

First we get the GTest source code:


```
sudo apt install libgtest-dev
```

GTest doesn't come precompiled unfortunately, so we need to build and install
the source code:

```
cd /usr/src/gtest          # Move to source dir
sudo cmake CMakeLists.txt  # Collect everything with cmake
sudo make                  # Comnpile source
sudo cp *.a /usr/lib       # Copy built libraries to lib dir
```

## Usage

### Manually

It can be difficult to cleanup CMake builds sometimes, so it's recommended to
create a separate build directory and work from there.

1. From the root directory of this repo (``gtest-example``), create your build
   directory and move there:

   ```
   mkdir _build && cd _build
   ```

2. Run CMake to setup the Makefile:

   ```
   cmake ..
   ```
   CMake uses the ``CMakeLists.txt`` file in the root directory, hence passing
   the parent directory (``..``) to ``cmake``.

3. CMake will have created a Makefile for you. You can now build the test
   executables:

   ```
   make
   ```

4. You will now have several executables named ``run*Tests``, where each
   executable is associated with a test suite (discussed below). Try running a
   test suite, for example:

   ```
   ./runSimpleTests
   ```

You can easily cleanup build artifacts by removing the entire build directory.
For example, from the root directory:

```
rm -r _build
```


### Scripts

TODO (probably with gcov)


## Test Suites

A brief description of each test suite.


### Simple Tests

Executable: ``runSimpleTests``

This test suite implements simple, explicit tests that do not use any additional infrastructure or reusable code.


### Failing Tests

Executable: ``runFailingTests``

This test suite is simply to demonstrate the difference between the built in
``ASSERT_*`` and ``EXPECT_*`` checks. Using ``EXPECT_*`` will prompt a
_non-fatal_ failure. That is to say any remaining code in the test case will
still be executed. Conversely, ``ASSERT_*`` checks will cause a _fatal_ failure
and the test case is abandoned immediately. In general it makes sense to use
``EXPECT_`` unless there are specific circumstances that warrant abandoning a
test mid execution.


### Fixture Tests

Executable: ``runFixtureTests``

This test suite demonstrates the use of the simple ``Test`` test fixture. Our
test fixture, ``MathsTest`` is defined in the ``fixture_tests.h`` header. The
fixture just creates an instance of our ``EasyMaths`` class with some hardcoded
values to avoid having to duplicate this setup for each of our test cases. In
the ``cpp`` file we ``TEST_F`` to pull our ``MathsTest`` fixture from the
header. The fixture name incidentally becomes the name of our test suite. Within
this test suite we define 4 tests, one for each of our member functions. Since
we have access to our local test variables ``a`` and ``b``, we can easily access
these to calculate an expected value in the test case itself. When running the
test suite, notice the output illustrating that the ``SetUp`` and ``TearDown``
functions from the fixture are automatically run before and after the test case
respectively.


### Parametric Tests

Executable: ``runParamTests``

Similar to the fixture tests, but using the parametric ``TestWithParam`` test
fixture. ``SweepTest`` is defined in the ``parametric_tests.h`` header and is
identical to to the one used in the fixture tests _except_ we now have a
parameter to be assigned. The ``TestWithParam`` class only accepts a single
parameter, but we can easily add additional parameters by making the single
available test parameter a tuple and unpacking that tuple during the test setup
or execution. In the ``cpp`` file we now use ``TEST_P`` to pull our
``SweepTest`` parametric fixture. We also must create a list of parameters with
which to run tests by using ``INSTANTIATE_TEST_CASE_P``. These parameter sets
are given a name and then tied to the parametric fixture/test suite (i.e.
``SweepTest``). You can have any number of parameter sets for a given test suite
but beware **if no values are assigned there is no warning or error and the
tests will simply be skipped**. Parameters can be explicitly specified using the
``Values`` wrapper, or combinations of parameters can be exhaustively combined
by using the ``Combine`` wrapper.


## General GTest Notes

- You don't need to write a ``main`` entry point to run GTest. If you link
  ``gtest_main`` during your compile GTest automatically handles this. If you
  have special circumstances, it is still possible to write your own ``main``
  though.
- You typically will want to use the ``EXPECT_*`` checks from GTest, but
  ``ASSERT_*`` checks are available if circumstances warrant it.
- If you are comparing floating point numbers, use the built in
  ``EXPECT_FLOAT_*`` which automatically handles floating point discrepancies.
- You can pipe a custom error message into the built in checks which can be
  useful for debugging. The built in checks also do a reasonable job of
  providing context to failures. The check arguments should passed in expected
  first, then your value in questions, for example
  ``EXPECT_EQ(expected_val, val_under_test) << "Custom message!"``.
  Take a look at the output of the failing tests to see this in play:

  ```
  /home/ben/git/gtest-example/test/src/failing_tests.cpp:12: Failure
  Value of: pass
    Actual: false
  Expected: true
  >> Expected non-fatal failure!
  ```

- The ``TEST*`` macros accept a fixture/suite name and a test case name. The
  fixture/suite name can and should be reused, but the test case name must be
  unique. For example ``TEST_F(FixtureName, TestCaseName){}``.


## TODO
- Typed tests (sweep template dtype)
- Add some functional tests
    - Mock things with FFF
- Add gcov/lcov
- Add clang-format/cppcheck/cpplint
    - pre-commit?
- Build/run scripts (probably with gcov)

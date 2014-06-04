// stl
#include <string>

// gtest
#include <gtest/gtest.h>

// img2term
#include "img2term/modifier.hxx"

namespace {

// The fixture for testing class Foo.
class ModifierTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  ModifierTest() {
    // You can do set-up work for each test here.
  }

  virtual ~ModifierTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(ModifierTest, TheyDance) {
const std::string input_filepath = "this/package/testdata/myinputfile.dat";
const std::string output_filepath = "this/package/testdata/myoutputfile.dat";
  EXPECT_EQ(0, 1);
}

// Tests that Foo does Xyz.
TEST_F(ModifierTest, AndSing) {
  // Exercises the Xyz feature of Foo.
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
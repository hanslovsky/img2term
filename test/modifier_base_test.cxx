// stl
#include <string>
#include <memory>
#include <iostream>

// vigra
#include <vigra/multi_array.hxx>
#include <vigra/unittest.hxx>

// gtest
#include <gtest/gtest.h>

// img2term
#include "img2term/modifier/modifier_base.hxx"

using namespace img2term;

class TestDecorator : public ModifierDecorator  {
 public:
  TestDecorator() : ModifierDecorator() {}
  TestDecorator( std::shared_ptr<ModifierBase> modifier, int N ) :
      ModifierDecorator( modifier ), N_( N )
  {}

  virtual std::string generate( const vigra::MultiArrayView<3, uint> patch ) const {
    std::string res = "TestDecorator" + std::to_string( N_ ) + " " + ModifierDecorator::generate( patch );
    return res;
  }

 private:
  int N_;

};

namespace {


// Tests that the Foo::Bar() method does Abc.
TEST(ModifierTest, Decorate) {

  std::shared_ptr<ModifierBase> m1( new ModifierBase );
  
  std::shared_ptr<ModifierBase> m2( new TestDecorator(  m1, 2 ) );

  TestDecorator dec( std::move( m2 ), 1 );

  auto test_string = dec.generate( vigra::MultiArray<3, uint>() );

  EXPECT_EQ( test_string, std::string( "TestDecorator1 TestDecorator2 " ) );

}

// Tests that Foo does Xyz.
TEST(ModifierTest, AndSing) {
  // Exercises the Xyz feature of Foo.
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

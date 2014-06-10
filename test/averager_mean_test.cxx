// stl
#include <string>
#include <memory>
#include <iostream>

// vigra
#include <vigra/multi_array.hxx>

// gtest
#include <gtest/gtest.h>

// img2term
#include "img2term/average/averager_mean.hxx"

using namespace img2term;

namespace {


// Tests that the Foo::Bar() method does Abc.
TEST( AveragerMeanTest, CallNoIntFloor ) {

  vigra::MultiArray<3, uint> patch( vigra::Shape3( 5, 3, 3 ) ); // average: 23
  uint count = 1;
  uint reference = 23;

  for ( auto& pixel : patch ) {
    pixel = count;
    ++count;
  }

  AveragerMean average;

  Color::VigraColor c = average( patch );

  EXPECT_EQ( reference, c[0] );

}



TEST( AveragerMeanTest, CallIntFloor ) {

  vigra::MultiArray<3, uint> patch( vigra::Shape3( 4, 3, 3 ) ); // average: 18,5 -> 18
  uint count = 1;
  uint reference = 18;

  for ( auto& pixel : patch ) {
    pixel = count;
    ++count;
  }

  AveragerMean average;

  Color::VigraColor c = average( patch );

  EXPECT_EQ( reference, c[0] );

}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

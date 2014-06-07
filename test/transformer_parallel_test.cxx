// stl
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>   // setfill, setw

// vigra
#include <vigra/multi_array.hxx>

// gtest
#include <gtest/gtest.h>

// img2term
#include "img2term/options.hxx"
#include "img2term/transformer/transformer_parallel.hxx"

using namespace img2term;


namespace {


// Tests that the Foo::Bar() method does Abc.
TEST(TransformerParallelTest, Decorate) {

  Options options;
  options.xStride = 16;
  options.yStride = 8;
  options.modifier_type = "1";

  vigra::MultiArray<3, uint> img(vigra::Shape3(50, 36, 3));

  TransformerParallel tp( img );
  auto vec = tp.generateString( options );

  std::cout << vec.size() << std::endl;
  for ( auto& it : vec ) {
    std::cout << it << std::endl;
  }

  options.modifier_type = "";
  vec = tp.generateString( options );
  std::cout << vec.size() << std::endl;
  
  for ( auto& it : vec ) {
    std::cout << it << std::endl;
  }
  
}

// Tests that Foo does Xyz.
TEST(TransformerParallelTest, AndSing) {
  // Exercises the Xyz feature of Foo.
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

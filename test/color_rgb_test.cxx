// stl
#include <string>
#include <algorithm>
#include <iostream>

// vigra
#include <vigra/multi_array.hxx>

// gtest
#include <gtest/gtest.h>

// img2term
#include "img2term/color/color_rgb.hxx"
#include "img2term/color/distance_l2_squared.hxx"


using namespace img2term;


namespace {


TEST( ColorRGBTest, ReturnAsciiColors ) {

  
  const auto& default_colors  = ColorRGB::RGB_256;
  ColorRGB cgs( std::shared_ptr<DistanceL2Squared>( new DistanceL2Squared ), default_colors );

  Color::VigraColor vc( vigra::Shape1( 3 ) );
  vc[0] = 255;
  vc[1] = 0;
  vc[2] = 0;

  cgs( vc );
  std::cout << cgs.to_string() << std::endl;
  

}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

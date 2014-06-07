// stl
#include <string>
#include <algorithm>

// vigra
#include <vigra/multi_array.hxx>

// gtest
#include <gtest/gtest.h>

// img2term
#include "img2term/color/color_gray_scale.hxx"

using namespace img2term;


namespace {


// Tests that the Foo::Bar() method does Abc.
TEST( ColorGrayScaleTest, CheckDefaultColors ) {

  auto default_colors = ColorGrayScale::default_colors;
  ColorGrayScale::IndexedColorVector
      default_colors_reference { std::make_pair( 11, " " ),
        std::make_pair(  34, "." ),
        std::make_pair(  57, "," ),
        std::make_pair(  80, ":" ),
        std::make_pair( 103, ";" ),
        std::make_pair( 126, "+" ),
        std::make_pair( 149, "*" ),
        std::make_pair( 172, "&" ),
        std::make_pair( 195, "#" ),
        std::make_pair( 218, "%" ),
        std::make_pair( 241, "@" )
        };

  ASSERT_EQ( default_colors, default_colors_reference );
        
        
}


TEST( ColorGrayScaleTest, ReturnAsciiColors ) {

  ColorGrayScale cgs;
  auto default_colors = ColorGrayScale::default_colors;
  int sign             = -1;
  const int add1       = 11;
  const int add2       = 12;

  for ( const auto& c : default_colors ) {
    sign *= -1;
    cgs( vigra::MultiArray<1, uint>( vigra::Shape1(1), (uint) ( sign * add1 + (int) c.first ) ) );
    ASSERT_EQ( cgs.to_string(), c.second );
  }

  sign = -1;

  for ( size_t i = 0; i < default_colors.size(); ++i ) {
    sign *= -1;
    cgs( vigra::MultiArray<1, uint>( vigra::Shape1(1), (uint) ( sign * add2 + (int) default_colors[i].first ) ) );
    ASSERT_EQ( cgs.to_string(), default_colors[ std::min( (int)i + sign, (int)default_colors.size() - 1 )].second );
  }

}


}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

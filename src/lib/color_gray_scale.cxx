// stl
#include <algorithm>      // min_element
#include <cstdlib>        // abs
#include <string>
#include <utility>        // pair
#include <vector>

// img2term
#include "img2term/color/color_gray_scale.hxx"


namespace img2term
{

// {' ', '.', ',', ':', ';', '+', '*', '&', '#', '%', '@'}
const ColorGrayScale::IndexedColorVector ColorGrayScale::default_colors =
    ColorGrayScale::create_indexed_color_vector(
        std::vector<ColorGrayScale::AsciiColor> { " ", ".",  ",", ":", ";", "+", "*", "&", "#", "%", "@"}
                                                );


const size_t ColorGrayScale::max_index_value = 255;


ColorGrayScale::IndexedColorVector
ColorGrayScale::create_indexed_color_vector( const std::vector<AsciiColor>& colors )
{
  size_t n_colors = colors.size();
  size_t step     = max_index_value / n_colors;
  
  IndexedColorVector result;

  size_t start = step / 2;
  for ( const auto& it : colors ) {
    result.push_back( std::make_pair( start, it ) );
    start += step;
  }

  return result;
}


ColorGrayScale::ColorGrayScale() :
    colors_( default_colors ),
    current_color_index_( -1 )
{
  
}


ColorGrayScale::ColorGrayScale( const IndexedColorVector& colors ) :
    colors_( colors ),
    current_color_index_( -1 )
{
  
}


std::string ColorGrayScale::to_string() const {
  return colors_[ current_color_index_ ].second;
}


void ColorGrayScale::operator() ( const VigraColor& color ) {
  auto index = std::min_element( colors_.begin(),
                                 colors_.end(),
                                 [color] ( const IndexedColor& c1, const IndexedColor& c2 ) {
                                   return ( abs( (int) c1.first - (int) color[0] ) <
                                            abs( (int) c2.first - (int) color[0] )
                                            );
                                 }
                                 );
  if ( index == colors_.end() )
  {
    current_color_index_ = -1;
  }
  else
  {
    current_color_index_ = index - colors_.begin();
  }
}
                                                       
} /* namespace img2term */

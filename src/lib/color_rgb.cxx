// stl
#include <string>
#include <utility>
#include <vector>
#include <cassert>
#include <memory>
// tmp
#include <iostream>
#include <iterator>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/color/color_base.hxx"
#include "img2term/color/color_rgb.hxx"
#include "img2term/color/distance.hxx"


namespace img2term
{

std::vector<Color::VigraColor> ColorRGB::generateVigraColor( const std::vector<uint>& uint_colors )
{
  assert( uint_colors.size() % 3 == 0 );
  std::vector<VigraColor> result;
  for ( size_t i = 0; i < uint_colors.size(); i += 3 )
  {
    result.push_back( VigraColor( vigra::Shape1( 3 ) ) );
    std::copy( uint_colors.begin() + i,
               uint_colors.begin() + std::min( i + 3, uint_colors.size() ),
               result.rbegin()->begin()
               );
  }
  return result;
}


ColorRGB::ColorRGB( std::shared_ptr<ColorDistance> distance, const std::vector<VigraColor>& colors ) :
    distance_( distance ),
    colors_( colors ),
    current_color_index_( 0 )
{

}



std::string ColorRGB::to_string() const
{
  return std::to_string( current_color_index_ ); // colors_[current_color_index_] );
}


void ColorRGB::operator() ( const VigraColor& color )
{
  double min_distance  = (* distance_ )( color, colors_[0] );
  
  
  {
    size_t count = 0;
    size_t tmp = 0;
    // std::ostream_iterator<unsigned int> out_it (std::cout, ",");
    for ( const auto& c : colors_ )
    {
      double curr_distance = ( *distance_ )( color, c );
      
      // std::cout << "input: ";                             
      // std::copy( color.begin(), color.end(), out_it );    
      // std::cout << " comparison: ";                       
      // std::copy( c.begin(), c.end(), out_it );            
      // std::cout << " distance: " << curr_distance << '\n';

      if ( curr_distance < min_distance )
      {
        min_distance = curr_distance;
        tmp          = count;
        // std::cout << "min_dist=" << min_distance << ", idx=" << tmp << std::endl;
      }
      ++count;
    }
    current_color_index_ = tmp;
  }
}


const std::vector<uint> ColorRGB::RGB_8_UINT =
{
  0, 0, 0,
  205, 0, 0,
  205, 205, 0,
  0, 0, 240,
  205, 0, 205,
  0, 205, 205,
  245, 245, 245
};


const std::vector<uint> ColorRGB::RGB_16_UINT =
{
  0, 0, 0,
  205, 0, 0,
  0, 205, 0,
  205, 205, 0,
  0, 0, 240,
  205, 0, 205,
  0, 205, 205,
  245, 245, 245,
  128, 128, 128,
  128, 0, 0,
  0, 128, 0,
  128, 128, 0,
  0, 0, 128,
  128, 128, 0,
  0, 128, 128,
  192, 192, 192
};


const std::vector<uint> ColorRGB::RGB_256_UINT =
{
  0, 0, 0,
  205, 0, 0,
  0, 205, 0,
  205, 205, 0,
  0, 0, 238,
  205, 0, 205,
  0, 205, 205,
  229, 229, 229,
  127, 127, 127,
  255, 0, 0,
  0, 255, 0,
  255, 255, 0,
  92, 92, 255,
  255, 0, 255,
  0, 255, 255,
  255, 255, 255,
  0, 0, 0,
  0, 0, 95,
  0, 0, 135,
  0, 0, 175,
  0, 0, 215,
  0, 0, 255,
  0, 95, 0,
  0, 95, 95,
  0, 95, 135,
  0, 95, 175,
  0, 95, 215,
  0, 95, 255,
  0, 135, 0,
  0, 135, 95,
  0, 135, 135,
  0, 135, 175,
  0, 135, 215,
  0, 135, 255,
  0, 175, 0,
  0, 175, 95,
  0, 175, 135,
  0, 175, 175,
  0, 175, 215,
  0, 175, 255,
  0, 215, 0,
  0, 215, 95,
  0, 215, 135,
  0, 215, 175,
  0, 215, 215,
  0, 215, 255,
  0, 255, 0,
  0, 255, 95,
  0, 255, 135,
  0, 255, 175,
  0, 255, 215,
  0, 255, 255,
  95, 0, 0,
  95, 0, 95,
  95, 0, 135,
  95, 0, 175,
  95, 0, 215,
  95, 0, 255,
  95, 95, 0,
  95, 95, 95,
  95, 95, 135,
  95, 95, 175,
  95, 95, 215,
  95, 95, 255,
  95, 135, 0,
  95, 135, 95,
  95, 135, 135,
  95, 135, 175,
  95, 135, 215,
  95, 135, 255,
  95, 175, 0,
  95, 175, 95,
  95, 175, 135,
  95, 175, 175,
  95, 175, 215,
  95, 175, 255,
  95, 215, 0,
  95, 215, 95,
  95, 215, 135,
  95, 215, 175,
  95, 215, 215,
  95, 215, 255,
  95, 255, 0,
  95, 255, 95,
  95, 255, 135,
  95, 255, 175,
  95, 255, 215,
  95, 255, 255,
  135, 0, 0,
  135, 0, 95,
  135, 0, 135,
  135, 0, 175,
  135, 0, 215,
  135, 0, 255,
  135, 95, 0,
  135, 95, 95,
  135, 95, 135,
  135, 95, 175,
  135, 95, 215,
  135, 95, 255,
  135, 135, 0,
  135, 135, 95,
  135, 135, 135,
  135, 135, 175,
  135, 135, 215,
  135, 135, 255,
  135, 175, 0,
  135, 175, 95,
  135, 175, 135,
  135, 175, 175,
  135, 175, 215,
  135, 175, 255,
  135, 215, 0,
  135, 215, 95,
  135, 215, 135,
  135, 215, 175,
  135, 215, 215,
  135, 215, 255,
  135, 255, 0,
  135, 255, 95,
  135, 255, 135,
  135, 255, 175,
  135, 255, 215,
  135, 255, 255,
  175, 0, 0,
  175, 0, 95,
  175, 0, 135,
  175, 0, 175,
  175, 0, 215,
  175, 0, 255,
  175, 95, 0,
  175, 95, 95,
  175, 95, 135,
  175, 95, 175,
  175, 95, 215,
  175, 95, 255,
  175, 135, 0,
  175, 135, 95,
  175, 135, 135,
  175, 135, 175,
  175, 135, 215,
  175, 135, 255,
  175, 175, 0,
  175, 175, 95,
  175, 175, 135,
  175, 175, 175,
  175, 175, 215,
  175, 175, 255,
  175, 215, 0,
  175, 215, 95,
  175, 215, 135,
  175, 215, 175,
  175, 215, 215,
  175, 215, 255,
  175, 255, 0,
  175, 255, 95,
  175, 255, 135,
  175, 255, 175,
  175, 255, 215,
  175, 255, 255,
  215, 0, 0,
  215, 0, 95,
  215, 0, 135,
  215, 0, 175,
  215, 0, 215,
  215, 0, 255,
  215, 95, 0,
  215, 95, 95,
  215, 95, 135,
  215, 95, 175,
  215, 95, 215,
  215, 95, 255,
  215, 135, 0,
  215, 135, 95,
  215, 135, 135,
  215, 135, 175,
  215, 135, 215,
  215, 135, 255,
  215, 175, 0,
  215, 175, 95,
  215, 175, 135,
  215, 175, 175,
  215, 175, 215,
  215, 175, 255,
  215, 215, 0,
  215, 215, 95,
  215, 215, 135,
  215, 215, 175,
  215, 215, 215,
  215, 215, 255,
  215, 255, 0,
  215, 255, 95,
  215, 255, 135,
  215, 255, 175,
  215, 255, 215,
  215, 255, 255,
  255, 0, 0,
  255, 0, 95,
  255, 0, 135,
  255, 0, 175,
  255, 0, 215,
  255, 0, 255,
  255, 95, 0,
  255, 95, 95,
  255, 95, 135,
  255, 95, 175,
  255, 95, 215,
  255, 95, 255,
  255, 135, 0,
  255, 135, 95,
  255, 135, 135,
  255, 135, 175,
  255, 135, 215,
  255, 135, 255,
  255, 175, 0,
  255, 175, 95,
  255, 175, 135,
  255, 175, 175,
  255, 175, 215,
  255, 175, 255,
  255, 215, 0,
  255, 215, 95,
  255, 215, 135,
  255, 215, 175,
  255, 215, 215,
  255, 215, 255,
  255, 255, 0,
  255, 255, 95,
  255, 255, 135,
  255, 255, 175,
  255, 255, 215,
  255, 255, 255,
  8, 8, 8,
  18, 18, 18,
  28, 28, 28,
  38, 38, 38,
  48, 48, 48,
  58, 58, 58,
  68, 68, 68,
  78, 78, 78,
  88, 88, 88,
  98, 98, 98,
  108, 108, 108,
  118, 118, 118,
  128, 128, 128,
  138, 138, 138,
  148, 148, 148,
  158, 158, 158,
  168, 168, 168,
  178, 178, 178,
  188, 188, 188,
  198, 198, 198,
  208, 208, 208,
  218, 218, 218,
  228, 228, 228,
  238, 238, 238
};


const std::vector<Color::VigraColor> ColorRGB::RGB_8   = ColorRGB::generateVigraColor( RGB_8_UINT );
const std::vector<Color::VigraColor> ColorRGB::RGB_16  = ColorRGB::generateVigraColor( RGB_16_UINT );
const std::vector<Color::VigraColor> ColorRGB::RGB_256 = ColorRGB::generateVigraColor( RGB_256_UINT );


} /* namespace img2term */

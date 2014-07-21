// stl
#include <memory>
#include <string>
#include <iostream>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/average/averager_mean.hxx"
#include "img2term/color/color_base.hxx"
#include "img2term/color/color_rgb.hxx"
#include "img2term/color/distance_l2_squared.hxx"
#include "img2term/matching/matching_color.hxx"


namespace img2term {

MatchingRGB::MatchingRGB() :
    averager_r_( new AveragerMean ),
    averager_g_( new AveragerMean ),
    averager_b_( new AveragerMean ),
    color_( new ColorRGB( std::shared_ptr<ColorDistance>( new DistanceL2Squared ), ColorRGB::RGB_256 ) )
{

}


MatchingRGB::MatchingRGB( AveragerPtr averager, ColorPtr color ) :
    averager_r_( averager ),
    averager_g_( averager ),
    averager_b_( averager ),
    color_( color )
{

}


std::string MatchingRGB::match( vigra::MultiArrayView<3, uint> patch ) const
{
  Color::VigraColor result( vigra::Shape1( 3 ) );
  result[0] = ( *averager_r_ )( patch.subarray( vigra::Shape3( 0, 0, 0 ),
                                                vigra::Shape3( patch.shape()[0], patch.shape()[1], 1 )
                                                )
                                )[0];
  
  result[1] = ( *averager_r_ )( patch.subarray( vigra::Shape3( 0, 0, 1 ),
                                                vigra::Shape3( patch.shape()[0], patch.shape()[1], 2 )
                                                )
                                )[0];

  result[2] = ( *averager_r_ )( patch.subarray( vigra::Shape3( 0, 0, 2 ),
                                                vigra::Shape3( patch.shape()[0], patch.shape()[1], 3 )
                                                )
                                )[0];

  // std::cout << result[0] << "," << result[1] << "," << result[2] << std::endl;

  (*color_)( result );
  return color_->to_string();

}


} /* namespace img2term */

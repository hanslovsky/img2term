// stl
#include <memory>
#include <string>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/average/averager_mean.hxx"
#include "img2term/color/color_base.hxx"
#include "img2term/color/color_gray_scale.hxx"
#include "img2term/matching/matching_gray_scale.hxx"


namespace img2term {

MatchingGrayScale::MatchingGrayScale() :
    averager_( new AveragerMean ),
    color_( new ColorGrayScale )
{

}


MatchingGrayScale::MatchingGrayScale( AveragerPtr averager, ColorPtr color ) :
    averager_( averager ),
    color_( color )
{

}


std::string MatchingGrayScale::match( vigra::MultiArrayView<3, uint> patch ) const
{
  (*color_)( (*averager_)( patch ) );
  return color_->to_string();

}


} /* namespace img2term */

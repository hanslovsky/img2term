// stl

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/color/color_base.hxx"
#include "img2term/average/averager_mean.hxx"


namespace img2term
{

Color::VigraColor AveragerMean::operator() ( const vigra::MultiArrayView<3, uint> patch ) const
{
  patch[0];
  

  vigra::MultiArray<1, uint> result( vigra::Shape1( 1 ), 0u );

  int count = 0;

  for ( const auto& pixel : patch ) {
    result[0] += pixel;
    ++count;
  }

  result[0] /= count;
  return result;

}
    


} /* namespace img2term */

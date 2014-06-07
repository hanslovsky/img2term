// vigra
#include <vigra/tinyvector.hxx>

// img2term
#include "img2term/color/color_base.hxx"


namespace img2term
{

Color::GrayScale Color::to_gray_scale( const RGB& rgb ) {
  return GrayScale( ( rgb[0] + rgb[1] + rgb[2] )/3.0 );
}


Color::RGB Color::to_rgb( const GrayScale& gray_scale ) {
  return RGB( gray_scale[0], gray_scale[0], gray_scale[0] );
}

}

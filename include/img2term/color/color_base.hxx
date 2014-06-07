#pragma once

// stl
#include <string>

// vigra
#include <vigra/multi_array.hxx>
#include <vigra/tinyvector.hxx>

namespace img2term
{

class Color {
 public:
  typedef vigra::TinyVector<uint, 1> GrayScale;
  typedef vigra::TinyVector<uint, 3> RGB;
  typedef vigra::MultiArrayView<1, uint> VigraColor;
  
  virtual std::string to_string() const = 0;
  virtual void operator() ( const VigraColor& color ) = 0;

  static GrayScale to_gray_scale( const RGB& rgb );
  static RGB to_rgb( const GrayScale& gray_scale );
};

} /* namespace img2term */

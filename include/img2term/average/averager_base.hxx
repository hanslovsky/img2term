#pragma once


// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/color/color_base.hxx"

namespace img2term {

class AveragerBase {

 public:
  virtual Color::VigraColor operator() ( const vigra::MultiArrayView<3, uint> patch ) const = 0;

};


} /* namespace img2term */

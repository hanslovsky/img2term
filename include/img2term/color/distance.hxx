#pragma once

// img2term
#include "img2term/color/color_base.hxx"

namespace img2term
{

class ColorDistance {
 public:
  virtual double operator()( const Color::VigraColor& c1, const Color::VigraColor& c2 ) const = 0;
  
};


} /* namespace img2term */

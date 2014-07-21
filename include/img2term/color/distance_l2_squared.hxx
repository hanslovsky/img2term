#pragma once

// img2term
#include "img2term/color/distance.hxx"
#include "img2term/color/color_base.hxx"

namespace img2term
{

class DistanceL2Squared : public ColorDistance {
 public:
  virtual double operator()( const Color::VigraColor& c1, const Color::VigraColor& c2 ) const;
  
};


} /* namespace img2term */

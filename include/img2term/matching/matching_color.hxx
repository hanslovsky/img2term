#pragma once

// stl
#include <memory>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/matching/matching_base.hxx"


namespace img2term
{

class ColorRGB;

class MatchingRGB : public MatchingBase
{
 public:
  typedef std::shared_ptr<ColorRGB> ColorPtr;

  MatchingRGB();
  MatchingRGB( AveragerPtr averager, ColorPtr color );

  virtual std::string match( vigra::MultiArrayView<3, uint> patch ) const;

 private:
  AveragerPtr averager_r_;
  AveragerPtr averager_g_;
  AveragerPtr averager_b_;
  
  ColorPtr color_;
  
};

} /* namespace img2term */


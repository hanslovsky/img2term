#pragma once

// stl
#include <memory>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/matching/matching_base.hxx"


namespace img2term
{

class ColorGrayScale;

class MatchingGrayScale : public MatchingBase
{
 public:
  typedef std::shared_ptr<ColorGrayScale> ColorPtr;

  MatchingGrayScale();
  MatchingGrayScale( AveragerPtr averager, ColorPtr color );

  virtual std::string match( vigra::MultiArrayView<3, uint> patch ) const;

 private:
  AveragerPtr averager_;
  ColorPtr color_;
};

} /* namespace img2term */


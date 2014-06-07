#pragma once

// stl
#include <memory>

// vigra
#include <vigra/multi_array.hxx>


namespace img2term
{

class ColorBase;

class MatchingBase
{
 public:
  typedef std::unique_ptr<ColorBase> ColorPtr;

  virtual ColorPtr match( vigra::MultiArrayView<3, uint> patch ) const;
};

} /* namespace img2term */

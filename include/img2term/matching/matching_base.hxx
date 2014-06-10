#pragma once

// stl
#include <memory>

// vigra
#include <vigra/multi_array.hxx>


namespace img2term
{

class ColorBase;

class Averager;

class MatchingBase
{
 public:
  typedef std::unique_ptr<ColorBase> ColorPtr;
  typedef std::unique_ptr<Averager> AveragerPtr;

  virtual ColorPtr match( vigra::MultiArrayView<3, uint> patch ) const;
};

} /* namespace img2term */

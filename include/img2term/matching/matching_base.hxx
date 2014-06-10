#pragma once

// stl
#include <memory>
#include <string>

// vigra
#include <vigra/multi_array.hxx>


namespace img2term
{

class AveragerBase;

class MatchingBase
{
 public:
  typedef std::shared_ptr<AveragerBase> AveragerPtr;

  virtual std::string match( vigra::MultiArrayView<3, uint> patch ) const = 0;
};

} /* namespace img2term */

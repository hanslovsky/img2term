#pragma once

namespace img2term
{

class Line;

class Options;

class LineFactory
{

 public:
  Line create( const Options& options) const;
  
};

} /* namespace img2term */


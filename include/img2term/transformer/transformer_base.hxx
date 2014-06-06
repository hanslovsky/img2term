#pragma once

// stl
#include <string>

// vigra
#include <vigra/multi_array.hxx>

namespace img2term {

class Options;

class TransformerBase {
 public:
  virtual std::vector<std::string> generateString( const Options& options ) const = 0;
};

} /* namespace img2term */

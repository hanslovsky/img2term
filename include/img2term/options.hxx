#pragma once

// stl
#include <string>

namespace img2term {

class Options {
 public:
  int xStride;
  int yStride;
  std::string modifier_type;
};

} /* namespace img2term */

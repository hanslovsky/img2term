#pragma once

// stl
#include <string>
#include <vector>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/transformer/transformer_base.hxx"

namespace img2term {

class Options;

class Line;

class TransformerParallel : public TransformerBase {
 public:
  TransformerParallel() = delete;
  TransformerParallel( const vigra::MultiArrayView<3, uint> image );
  
  virtual std::vector<std::string> generateString( const Options& options ) const;

 private:
  const vigra::MultiArrayView<3, uint> image_;
};

}

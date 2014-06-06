#pragma once

// stl
#include <string>
#include <memory>

// vigra
#include <vigra/multi_array.hxx>


namespace img2term
{

class ModifierBase;

class Options;

class Line
{
 public:
  Line() = delete;
  Line( std::shared_ptr<ModifierBase> modifier, const Options& options );

  std::string operator() ( const vigra::MultiArrayView<3, uint> row ) const;
 private:
  std::shared_ptr<ModifierBase> modifier_;
  const Options& options_;
};



} /* namespace img2term */

#pragma once

// stl
#include <memory>
#include <string>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/modifier/modifier_base.hxx"

namespace img2term {

class AveragingStrategyBase;

class ModifierColor : public ModifierDecorator {
 public:
  typedef std::shared_ptr<AveragingStrategyBase> AveragingStrategyPtr;

  ModifierColor() = delete;
  ModifierColor( AveragingStrategyPtr );
 protected:
  virtual std::string generate_own_string( vigra::MultiArrayView<3, uint> patch ) const;
 private:
  AveragingStrategyPtr averaging_;
};

} /* namespace img2term */

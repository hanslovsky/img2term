#pragma once

// stl
#include <memory>
#include <string>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/modifier/modifier_base.hxx"

namespace img2term {

class ModifierIncrement : public ModifierDecorator {
 public:
  ModifierIncrement();
  ModifierIncrement( int count );
  ModifierIncrement( int count, std::shared_ptr<ModifierBase> modifier );
 protected:
  virtual std::string generate_own_string( vigra::MultiArrayView<3, uint> patch ) const;
 private:
  mutable int count_; // this is mutable, because this is only a toy case.
};

} /* namespace img2term */

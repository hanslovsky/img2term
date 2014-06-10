#pragma once

// stl
#include <memory>
#include <string>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/modifier/modifier_base.hxx"

namespace img2term {

class MatchingBase;

class ModifierColor : public ModifierDecorator {
 public:
  typedef std::shared_ptr<MatchingBase> MatchingPtr;

  ModifierColor() = delete;
  ModifierColor( MatchingPtr );
  ModifierColor( std::shared_ptr<ModifierBase> modifier, MatchingPtr matching_ );
 protected:
  virtual std::string generate_own_string( vigra::MultiArrayView<3, uint> patch ) const;
 private:
  MatchingPtr matching_;
};

} /* namespace img2term */

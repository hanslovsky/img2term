#pragma once

// stl
#include <memory>
#include <string>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/modifier/modifier_base.hxx"

namespace img2term {

class MatchingStrategyBase;

class ModifierColor : public ModifierDecorator {
 public:
  typedef std::unique_ptr<MatchingStrategyBase> MatchingPtr;

  ModifierColor() = delete;
  ModifierColor( MatchingPtr );
 protected:
  virtual std::string generate_own_string( vigra::MultiArrayView<3, uint> patch ) const;
 private:
  MatchingPtr matching_;
};

} /* namespace img2term */

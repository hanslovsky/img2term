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

class ModifierRGB : public ModifierDecorator {
 public:
  typedef std::shared_ptr<MatchingBase> MatchingPtr;

  ModifierRGB() = delete;
  ModifierRGB(std::shared_ptr<ModifierBase> modifier,
              std::vector<std::shared_ptr<ModifierBase> > modifiers,
              MatchingPtr matching );
 protected:
  virtual std::string generate_own_string( vigra::MultiArrayView<3, uint> patch ) const;
 private:
  MatchingPtr matching_;

  std::vector<std::shared_ptr<ModifierBase> > modifiers_;
};

} /* namespace img2term */

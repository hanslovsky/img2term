#pragma once

// stl
#include <memory>
#include <string>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/modifier/modifier_base.hxx"

namespace img2term {

class ModifierConstant : public ModifierDecorator {
 public:
  ModifierConstant() = delete;
  ModifierConstant( const std::string& modifier_string_pre, const std::string& modifier_string_pre,  );
  ModifierConstant( const std::string& modifier_string, std::shared_ptr<ModifierBase> modifier );

  virtual std::string generate( vigra::MultiArrayView<3, uint> patch ) const;

 protected:
  virtual std::string generate_own_string( vigra::MultiArrayView<3, uint> patch ) const;
 private:
  const std::string& modifier_string_pre_;
  const std::string& modifier_string_post_;
};

} /* namespace img2term */

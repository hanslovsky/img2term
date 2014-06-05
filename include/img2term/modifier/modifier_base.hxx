#pragma once

// stl
#include <string>
#include <memory>

// vigra
#include <vigra/multi_array.hxx>


namespace img2term {

class ModifierBase {
 public:
  ModifierBase();
  virtual ~ModifierBase();
  virtual std::string generate( const vigra::MultiArrayView<3, uint> patch ) const;
};


class ModifierDecorator : public ModifierBase {
 public:
  ModifierDecorator();
  ModifierDecorator( std::shared_ptr<ModifierBase> );
  virtual ~ModifierDecorator();
  virtual std::string generate( const vigra::MultiArrayView<3, uint> patch ) const;
 protected:
  virtual std::string generate_own_string( const vigra::MultiArrayView<3, uint> patch ) const;
 private:
  std::shared_ptr<ModifierBase> modifier_;
};
  
} /* namespace img2term */

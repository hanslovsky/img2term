// stl
#include <string>
#include <memory>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/modifier/modifier_base.hxx"
#include "img2term/modifier/modifier_constant.hxx"

namespace img2term

{

ModifierConstant::ModifierConstant( const std::string& modifier_string ) :
    ModifierDecorator(),
    modifier_string_( modifier_string )
{

}


ModifierConstant::ModifierConstant( const std::string& modifier_string, std::shared_ptr<ModifierBase> modifier ) :
    ModifierDecorator( modifier ),
    modifier_string_( modifier_string )
{

}


std::string ModifierConstant::generate_own_string( vigra::MultiArrayView<3, uint> /* patch */ ) const {
  return modifier_string_;
}

}

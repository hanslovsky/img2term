// stl
#include <string>
#include <memory>
#include <iostream>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/modifier/modifier_base.hxx"
#include "img2term/modifier/modifier_increment.hxx"

namespace img2term

{

ModifierIncrement::ModifierIncrement() :
    ModifierDecorator(),
    count_(0)
{
      
}

ModifierIncrement::ModifierIncrement( int count ) :
    ModifierDecorator(),
    count_( count )
{

}


ModifierIncrement::ModifierIncrement( int count, std::shared_ptr<ModifierBase> modifier ) :
    ModifierDecorator( modifier ),
    count_( count )
{

}


std::string ModifierIncrement::generate_own_string( vigra::MultiArrayView<3, uint> /* patch */ ) const {
  size_t padding = 4;
  std::string ret = std::to_string( count_++ );
  if ( padding > ret.size() ) {
    ret.insert( 0, padding - ret.size(), ' ');
  }
  return ret;
}

}

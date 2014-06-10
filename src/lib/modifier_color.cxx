// stl
#include <string>
#include <memory>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/matching/matching_base.hxx"
#include "img2term/modifier/modifier_base.hxx"
#include "img2term/modifier/modifier_color.hxx"

namespace img2term

{

ModifierColor::ModifierColor( MatchingPtr matching_ ) :
    ModifierDecorator(),
    matching_( matching_ )
{

}


ModifierColor::ModifierColor( std::shared_ptr<ModifierBase> modifier, MatchingPtr matching_ ) :
    ModifierDecorator( modifier ),
    matching_( matching_ )
{

}


std::string ModifierColor::generate_own_string( vigra::MultiArrayView<3, uint> patch ) const {
  return matching_->match( patch );
}

}

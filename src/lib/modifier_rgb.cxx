// stl
#include <string>
#include <memory>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/matching/matching_base.hxx"
#include "img2term/modifier/modifier_base.hxx"
#include "img2term/modifier/modifier_rgb.hxx"

namespace img2term

{

ModifierRGB::ModifierRGB( std::shared_ptr<ModifierBase> modifier,
                          std::vector<std::shared_ptr<ModifierBase> > modifiers,
                          MatchingPtr matching ) :
    ModifierDecorator( modifier ),
    matching_( matching ),
    modifiers_( modifiers )
{

}


std::string ModifierRGB::generate_own_string( vigra::MultiArrayView<3, uint> patch ) const {
  const auto match_color = matching_->match( patch );
  std::string result     = "";

  for ( const auto& m : modifiers_ )
  {
    result += m->generate( patch ) + match_color + "m";
  }

  return result;
}

}

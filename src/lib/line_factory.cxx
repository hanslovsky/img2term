// stl
#include <memory>

// img2term
#include "img2term/line.hxx"
#include "img2term/options.hxx"
#include "img2term/line/line_factory.hxx"
#include "img2term/matching/matching_color.hxx"
#include "img2term/matching/matching_gray_scale.hxx"
#include "img2term/modifier/modifier_color.hxx"
#include "img2term/modifier/modifier_constant.hxx"
#include "img2term/modifier/modifier_increment.hxx"
#include "img2term/modifier/modifier_rgb.hxx"


namespace img2term
{

Line LineFactory::create( const Options& options ) const {
  if ( options.modifier_type == "" )
  {
    return Line( std::shared_ptr<ModifierBase> ( new ModifierIncrement( 0 ) ), options );
  } else if ( options.modifier_type == "gray")
  {
    ModifierColor::MatchingPtr mgs( new MatchingGrayScale );
    std::shared_ptr<ModifierBase> mb ( new ModifierColor( mgs ) );
    return Line( mb, options );
  } else if ( options.modifier_type == "color_with_bg" )
  {
    

    std::string bg_string( "\033[38;05;" );
    std::string fg_string( "\033[48;05;" );
    
    std::vector< std::shared_ptr<ModifierBase> > modifiers;
    // modifiers.push_back( std::shared_ptr<ModifierBase> ( new ModifierConstant( bg_string ) ) );
    modifiers.push_back( std::shared_ptr<ModifierBase> ( new ModifierConstant( fg_string ) ) );

    std::shared_ptr<ModifierBase> mb ( new ModifierRGB( std::shared_ptr<ModifierBase> (new ModifierConstant( " ") ),
                                                        modifiers,
                                                        std::shared_ptr<MatchingBase> (new MatchingRGB)
                                                        )
                                       );

    return Line( mb, options );



  } else
  {
    return Line( std::shared_ptr<ModifierBase> ( new ModifierConstant( options.modifier_type ) ), options );
  }
}

} /* namespace img2term */

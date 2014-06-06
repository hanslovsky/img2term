// stl
#include <memory>

// img2term
#include "img2term/line.hxx"
#include "img2term/options.hxx"
#include "img2term/line/line_factory.hxx"
#include "img2term/modifier/modifier_constant.hxx"


namespace img2term
{

Line LineFactory::create( const Options& options ) const {
  return Line( std::shared_ptr<ModifierBase> ( new ModifierConstant( options.modifier_type ) ), options );
}

} /* namespace img2term */


// stl
#include <string>
#include <memory>


// img2term
#include "img2term/line.hxx"
#include "img2term/modifier.hxx"
#include "img2term/options.hxx"

namespace img2term
{

Line::Line( std::unique_ptr<ModifierBase> modifier, std::shared_ptr<Options> options ) :
    modifier_( std::move( modifier ) ),
    options_( options )
{
  
}


std::string&& Line::transform( const vigra::MultiArrayView<3, uint> row )
{
  typedef vigra::MultiArray<3, uint>::difference_type Shape;
  std::string res;
  for ( int xLow = 0; xLow < row.shape()[0]; xLow += options_->xStride )
  {
    const vigra::MultiArrayView<3, uint> patch = row.subarray
        (
        Shape( xLow, 0, 0 ),
        Shape( xLow + options_->xStride, row.shape()[1], row.shape()[2] )
        );
    res.append( modifier_->generate( patch ) );
  }
  return std::move( res );
}

} /* namespace img2term */

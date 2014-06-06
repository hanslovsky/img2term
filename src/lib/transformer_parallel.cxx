// stl
#include <algorithm>
#include <future>
#include <string>
#include <vector>


// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/transformer/transformer_parallel.hxx"
#include "img2term/options.hxx"
#include "img2term/line.hxx"
#include "img2term/line/line_factory.hxx"


namespace img2term {

TransformerParallel::TransformerParallel( const vigra::MultiArrayView<3, uint> image ) :
    image_( image )
{
  // nothing to be done here
}


std::vector<std::string> TransformerParallel::generateString( const Options& options ) const
{
  std::vector<std::string> line_strings; // ( . Y . )
  Line line = LineFactory().create( options );
  for ( long y = 0; y < image_.shape()[1]; y += options.yStride )
  {
    size_t curr_stride = std::min( y + options.yStride, image_.shape()[1] ) - y;
    if ( curr_stride == 0 ) {
      break;
    }
    const vigra::MultiArrayView<3, uint> subarray = image_.subarray(
        vigra::Shape3( 0, y, 0 ),
        vigra::Shape3( image_.shape()[0], y + curr_stride, image_.shape()[2] )
                                                                    );
    auto future = std::async( line, subarray );
    line_strings.push_back( future.get() );
                    
  }
  return line_strings;
}

}

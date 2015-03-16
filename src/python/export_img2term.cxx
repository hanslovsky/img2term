#define PY_ARRAY_UNIQUE_SYMBOL my_module_PyArray_API
#define NO_IMPORT_ARRAY

#include <string>

#include <boost/python.hpp>

#include <vigra/multi_array.hxx>
#include <vigra/numpy_array.hxx>
#include <vigra/numpy_array_converters.hxx>

#include "img2term/options.hxx"
#include "img2term/transformer/transformer_parallel.hxx"

class PyTransformerParallel {
public:
  std::string generateString( const vigra::NumpyArray< 3, uint >& img, 
					   const img2term::Options& opt ) { 
    auto vec = img2term::TransformerParallel( img ).generateString( opt );
    std::string result = "";
    if ( vec.size() ) {
      auto it = vec.begin();
      result += *it;
      for( ; it != vec.end(); ++it )
	result += "\n" + *it;
    }
    return result;
  }
};

void export_img2term() {
  boost::python::class_< PyTransformerParallel > ( "TransformerParallel" ).
    def( "generateString", vigra::registerConverters( &PyTransformerParallel::generateString ) );
}
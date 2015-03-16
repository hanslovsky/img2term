#define PY_ARRAY_UNIQUE_SYMBOL my_module_PyArray_API

#include <boost/python.hpp>

#include <vigra/numpy_array_converters.hxx>

//forward declarations
void export_img2term();
void export_options();

BOOST_PYTHON_MODULE( libpyimg2term )
{
  vigra::import_vigranumpy();
  
    export_img2term();
    export_options();
}
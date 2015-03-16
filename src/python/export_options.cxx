#define PY_ARRAY_UNIQUE_SYMBOL my_module_PyArray_API
#define NO_IMPORT_ARRAY

#include <boost/python.hpp>

#include "img2term/options.hxx"

void export_options() {
  boost::python::class_< img2term::Options >( "Options" ).
    def_readwrite( "modifier_type", &img2term::Options::modifier_type ).
    def_readwrite( "xStride", &img2term::Options::xStride ).
    def_readwrite( "yStride", &img2term::Options::yStride );
}
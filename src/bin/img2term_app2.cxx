// stl
#include <string>
#include <iostream>

// vigra
#include <vigra/multi_array.hxx>
#include <vigra/imageinfo.hxx>
#include <vigra/impex.hxx>

// img2term
#include "img2term/line.hxx"
#include "img2term/line/line_factory.hxx"
#include "img2term/matching/matching_gray_scale.hxx"
#include "img2term/modifier/modifier_color.hxx"
#include "img2term/options.hxx"
#include "img2term/transformer/transformer_parallel.hxx"

using namespace img2term;

int main ( int argc, char** argv ) {

  
  if ( argc != 2 ) {
    return 1;
  }
  

  std::string filename( argv[1] );

  std::cout << "bla" << std::endl;

  vigra::ImageImportInfo info( filename.c_str() );

  std::cout << "Image information:\n";
  std::cout << "  file format: " << info.getFileType() << std::endl;
  std::cout << "  width:       " << info.width() << std::endl;
  std::cout << "  height:      " << info.height() << std::endl;
  std::cout << "  pixel type:  " << info.getPixelType() << std::endl;
  std::cout << "  color image: ";
  if (info.isColor())    std::cout << "yes (";
  else                        std::cout << "no  (";
  std::cout << "number of channels: " << info.numBands() << ")\n";

  vigra::MultiArray<3, uint> image( vigra::Shape3( info.width(), info.height(), 1 ) );

  vigra::MultiArray<2, vigra::UInt8> image_dummy( info.shape() );

  importImage( info, destImage( image_dummy ) );


  auto it = image.begin();
  for ( const auto& i : image_dummy ) {
    *it = i;
    ++it;
  }


  std::cout << image_dummy.shape() << std::endl;

  Options opt;
  opt.xStride = 3;
  opt.yStride = 5;
  opt.modifier_type = "gray";
  
  TransformerParallel t{ image };
  auto str = t.generateString( opt );
  for ( const auto& s : str ) {
    std::cout << s << std::endl;
  }

}

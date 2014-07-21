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
#include "img2term/modifier/modifier_constant.hxx"
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

  vigra::MultiArray<3, uint> image( vigra::Shape3( info.width(), info.height(), 3 ) );

  vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > image_dummy( info.shape() );

  importImage( info, destImage( image_dummy ) );

  std::cout << image.shape() << "," << image_dummy.shape() <<std::endl;

  for ( int x = 0; x < info.shape()[0]; ++x ) {
    for ( int y = 0; y < info.shape()[1]; ++y ) {
      for ( int c = 0; c < 3; ++c ){
        image(x, y, c) = image_dummy(x, y)[c];
      }
    }
  }



  

  std::cout << "read image: " << image_dummy.shape() << std::endl;

  Options opt;
  opt.xStride = info.width() / 200;
  opt.yStride = opt.xStride * 2.2;
  opt.modifier_type = "color_with_bg"; // gray";
  
  TransformerParallel t{ image };
  auto str = t.generateString( opt );
  for ( const auto& s : str ) {
    std::cout << s << std::endl;
  }

}

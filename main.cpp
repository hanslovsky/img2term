// stl
#include <algorithm>
#include <iostream>
#include <string>

// vigra
#include <vigra/multi_array.hxx>
#include <vigra/imageinfo.hxx>
#include <vigra/impex.hxx>


// img2term
#include "img2term/img2term.hxx"
#include "img2term/averaging/averagingmean.hxx"
#include "img2term/averaging/averagingfunctor.hxx"
#include "img2term/matching/matchingfunctor.hxx"
#include "img2term/matching/matchinggrayscale.hxx"
#include "img2term/matching/matchingrgbwithstate.hxx"

template <typename CLASS>
void doTest(CLASS c)
{
	std::cout << c() << std::endl;
}

std::string ock() { return "ock"; }

using namespace img2term;

int main(int, char**) {
	const std::string fn = "/home/phil/Downloads/terminator.jpg";
	vigra::ImageImportInfo info{ fn.c_str() };
	std::cout << "Image information:\n";
	std::cout << "  file format: " << info.getFileType() << std::endl;
	std::cout << "  width:       " << info.width() << std::endl;
	std::cout << "  height:      " << info.height() << std::endl;
	std::cout << "  pixel type:  " << info.getPixelType() << std::endl;
	std::cout << "  color image: ";
	if (info.isColor())    std::cout << "yes (";
	else                        std::cout << "no  (";
	std::cout << "number of channels: " << info.numBands() << ")\n";
	
	Image<uint, 3> image( info.shape() );
	int stepX = 10;
	int stepY = 20;
	vigra::importImage( info, vigra::destImage( image ) );
// 	for ( const auto& i : image ) std::cout << i << std::endl;
	
// 	auto image = img2term::Image<uint, 3>(5,10); // width, height
// 	*( image.begin()->begin() ) = 5;
	std::cout << *(image.begin()+(1920*540+960)) << std::endl;
	img2term::MatchingGrayScale<uint, 3> match{};
	auto match2 = img2term::MatchingFunctor<uint, 3>( [](const PixelType<uint, 3>&) -> std::string{ return "ALPHA BETA GAMMA"; }  );
	std::cout << match.match( *(image.begin()+(1920*540+960)) ) << std::endl;
	doTest([]() -> std::string {return "MIZZGE";});
	doTest(&ock);
	
// 	AveragingFunctor<uint, double, 3>( [](const ImageView<uint, 3>& img, PixelType<double, 3>& mean) -> void { mean += 
// *(img.begin()+(1920*540+960)); } )( 
// image, mean );
// 	std::cout << mean << std::endl;
	MatchingRGBWithState<double, 3> state;
	std::stringstream ss;
	for ( int y = 0; y < info.height(); y += stepY )
	{
		int yMax = std::min( y + stepY, info.height() );
// 		std::cout << y << std::endl;
		for ( int x = 0; x < info.width(); x += stepX )
		{
// 			std::cout << x << std::endl;
			int xMax = std::min( x + stepX, info.width() );
			vigra::Shape2 lower { x, y };
			vigra::Shape2 upper { xMax, yMax };
			const auto& subarray = image.subarray( lower, upper );
// 			std::cout << subarray.shape() << std::endl;
			PixelType< double, 3 > mean;
			AveragingMean<uint, double, 3>()( subarray, mean );
			ss << state.match( mean );
		}
		ss << '\n';
	}
	std::cout << ss.str() << std::endl;
	std::cout << state.match( PixelType<double, 3>() ) << std::endl;
    return 0;
}

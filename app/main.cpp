// stl
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// boost
#include <boost/program_options.hpp>

// vigra
#include <vigra/multi_array.hxx>
#include <vigra/imageinfo.hxx>
#include <vigra/impex.hxx>


// img2term
#include "img2term/img2term.hxx"
#include "img2term/img2term_colors.hxx"
#include "img2term/averaging/averagingmean.hxx"
#include "img2term/averaging/averagingfunctor.hxx"
#include "img2term/matching/matchingbase.hxx"
#include "img2term/matching/matchingfunctor.hxx"
#include "img2term/matching/matchinggrayscale.hxx"
#include "img2term/matching/matchingrgbwithstate.hxx"

// img2term_app
#include "img2term/app/register.hxx"
#include "img2term/app/typedefs.hxx"

namespace img2term
{
	std::map<std::string,  MethodPair> mapping = RegisterManager::getMethodsAndOptions();
}

using namespace img2term;



class HelpRequested : public bpo::error
{
public:
	HelpRequested() = default;
	HelpRequested( const std::string& message ) : bpo::error( message ) {};
};

auto readOptions( int argc, char** argv, bpo::variables_map& vm )
{
	auto desc = bpo::options_description{ "img2term options" };
	
// 	register_methods();
	
	desc.add_options()
		( "help,h", "Print help" )
		( "method,m", bpo::value<std::string>()->default_value( "color" ), "Method for converting image to term representation." )
		( "step-x,x", bpo::value<int>()->default_value( 10 ), "Width of patches to be represented by char (sequence)." )
		( "step-y,y", bpo::value<int>()->default_value( 20 ), "Height of patches to be represented by char (sequence)." )
		;
		
	auto desc_visible = desc;
	for ( const auto& o : mapping )
		desc_visible.add( o.second.second );

		;
	// positional options, not visible to user
	desc.add_options()
		( "filename", bpo::value< std::vector<std::string> >()->required(), "Input files" );
		;
	
	bpo::positional_options_description pos;
	pos.add( "filename", -1 );
	
	auto print_help = [&desc_visible,&pos] ( auto& stream )
	{
		stream << "\nimg2term [options] filename [filename...]\n" << std::endl << desc_visible << std::endl;
	};
		
	try {
		bpo::store(
			bpo::command_line_parser( argc, argv )
				.options( desc )
				.allow_unregistered()
				.positional( pos )
				.run()
				,
			vm
		);
		if ( vm.count("help")  )
		{
			print_help( std::cout );
			throw HelpRequested("Asked for help!");
		}
		
		std::string method = vm["method"].as<std::string>();
		const auto& mp = std::find_if( begin( mapping ), end( mapping ), [&method] ( const auto& s ) { return s.first == method; } );
		if( mp == end( mapping ) )
		{
			throw bpo::error( "'" + method + "'" + " not a legal choice for --method." );
		}
		else
		{
			bpo::store(
				bpo::command_line_parser( argc, argv )
					.options( desc.add( mp->second.second ) )
					.positional( pos )
					.run()
					,
				vm
			);
				
		}
	
	
		bpo::notify( vm );
	} catch ( const HelpRequested& h )
	{
		throw h;
	} catch ( const bpo::error& e )
	{
		print_help( std::cerr );
		std::cerr << e.what() << std::endl;
		throw e;
	}
	
	return desc;
}

int main( int argc, char** argv ) {
	
	bpo::variables_map vm;
	
	try {
		readOptions( argc, argv, vm );
	} catch ( const HelpRequested& e )
	{
		return 1;
	} catch ( std::exception& e )
	{
		return 2;
	}
	
	const std::string fn = vm["filename"].as<std::vector<std::string> >()[0];
	vigra::ImageImportInfo info{ fn.c_str() };
	
	Image<uint, 3> image( info.shape() );
	int stepX = vm["step-x"].as<int>();
	int stepY = vm["step-y"].as<int>();
	vigra::importImage( info, vigra::destImage( image ) );
	
	const std::string& method = vm["method"].as<std::string>();
	
	std::unique_ptr<MatchingBase<double, 3> > match = mapping[method].first( vm );
	const std::string end_of_line = method == "color" ? "\033[m" : "";
	std::stringstream ss;
	for ( int y = 0; y < info.height(); y += stepY )
	{
		int yMax = std::min( y + stepY, info.height() );
		for ( int x = 0; x < info.width(); x += stepX )
		{
			int xMax = std::min( x + stepX, info.width() );
			vigra::Shape2 lower { x, y };
			vigra::Shape2 upper { xMax, yMax };
			const auto& subarray = image.subarray( lower, upper );
			PixelType< double, 3 > mean;
			AveragingMean<uint, double, 3>()( subarray, mean );
			ss << match->match( mean );
		}
		ss << end_of_line << '\n';
	}
	std::cout << ss.str();
	std::cout.flush();
    return 0;
}

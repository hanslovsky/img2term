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
#include "img2term/matching/matchingfunctor.hxx"
#include "img2term/matching/matchinggrayscale.hxx"
#include "img2term/matching/matchingrgbwithstate.hxx"

using namespace img2term;
namespace bpo = boost::program_options;

class HelpRequested : public bpo::error
{
public:
	HelpRequested() = default;
	HelpRequested( const std::string& message ) : bpo::error( message ) {};
};

auto readOptions( int argc, char** argv, bpo::variables_map& vm )
{
	auto desc = bpo::options_description{ "img2term options" };
	auto desc_color = bpo::options_description{ "color method options for --method=color" };
	auto desc_grayscale = bpo::options_description{ "grayscale method options for --method=grayscale" };
	auto desc_combined = bpo::options_description{ "combined color and grayscale method options for --method=combined" };
	
	auto legal_methods = { "color", "grayscale", "combined" };
	
	desc.add_options()
		( "help,h", "Print help" )
		( "method,m", bpo::value<std::string>()->default_value( "color" ), "Method for converting image to term representation." )
		( "step-x,x", bpo::value<int>()->default_value( 10 ), "Width of patches to be represented by char (sequence)." )
		( "step-y,y", bpo::value<int>()->default_value( 20 ), "Height of patches to be represented by char (sequence)." )
		;
		
	desc_color.add_options()
		( "char-sequence,c", bpo::value<std::string>()->default_value( "@" ), "Character sequence representing one pixel in color mode." )
		( "color-background,b", bpo::value<bool>()->default_value( false ), "Paint background." )
		( "color-foreground,f", bpo::value<bool>()->default_value( true ),  "Paint foreground." )
		( "n-colors,n", bpo::value<int>()->default_value( 256 ), "Number of colors to be used (8,16,256)." )
		;
		
	desc_grayscale.add_options()
		( "char-sequence,c", bpo::value<std::string>()->default_value( GRAYSCALE_DEFAULT ),
		  "Character sequence representing one pixel in color mode." )
		;
		
	desc_combined.add_options()
		( "char-sequence,c", bpo::value<std::string>()->default_value( GRAYSCALE_DEFAULT ),
		  "Character sequence representing one pixel in color mode." )
		( "n-colors,n", bpo::value<int>()->default_value( 256 ), "Number of colors to be used (8,16,256)." )
		;
		
	auto desc_visible = desc;
	desc_visible
		.add( desc_color )
		.add( desc_grayscale )
		.add( desc_combined )
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
		if( std::find( begin( legal_methods ), end( legal_methods ), method ) == end( legal_methods ) )
		{
			throw bpo::error( "'" + method + "'" + " not a legal choice for --method." );
		} else if ( method == "color" )
		{
			bpo::store(
				bpo::command_line_parser( argc, argv )
				.options( desc.add( desc_color ) )
				.positional( pos )
				.run()
				,
			  vm
			);
		} else if ( method == "grayscale" )
		{
			bpo::store(
				bpo::command_line_parser( argc, argv )
				.options( desc.add( desc_grayscale ) )
				.positional( pos )
				.run()
				,
			  vm
			);
		} else if ( method == "combined" )
		{
			bpo::store(
				bpo::command_line_parser( argc, argv )
				.options( desc.add( desc_combined ) )
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

	
	auto create_match = [&vm]( const std::string& method_string, const std::string& char_sequence ) -> std::unique_ptr<MatchingBase<double, 
3> >
	{
		MatchingBase<double, 3>* result = nullptr;
		if ( method_string == "color" || method_string == "combined" )
		{
			bool fg = method_string == "color" ? vm["color-foreground"].as<bool>() : true;
			bool bg = method_string == "color" ? vm["color-background"].as<bool>() : false;
			auto selector = [fg,bg,&vm] ( auto pixel ) -> std::string 
			{
				double minimum_distance = std::numeric_limits< double >::max();
				int minimum_index = 0;
				int n_colors = vm["n-colors"].as<int>();
				auto colors = n_colors == 8 ? get_colors<8>() : n_colors == 16 ? get_colors<16>() : get_colors<256>();
				for( auto c = std::begin( colors ); c != std::end( colors ); ++c )
				{
					double distance = 0.0;
					for ( uint i = 0; i < c->size(); ++i )
					{
						double diff = pixel[i] - *( begin( *c ) +i );
						distance += diff*diff;
					}
					if ( distance < minimum_distance )
					{
						minimum_distance = distance;
						minimum_index = c - std::begin( COLOR_256 );
					}
				}
				std::stringstream ss;
				if ( fg )
					ss << "\033[38;05;" << minimum_index << "m";
				if ( bg )
					ss << "\033[48;05;" << minimum_index << "m";
				return ss.str();
			};
			if ( method_string == "color" )
				result = new MatchingRGBWithState<double, 3>( char_sequence, selector );
			else
			{
				MatchingGrayScale<double, 3> gs{ &*std::begin( char_sequence ), &*std::end( char_sequence ) };
				result = new MatchingRGBWithState<double, 3>( [gs] ( const auto& patch ) { return gs.match( patch ); }, selector );
			}
		}
		else if ( method_string == "grayscale" )
			result = new MatchingGrayScale<double, 3>( &*std::begin( char_sequence ), &*std::end( char_sequence ) );
		else
			result = nullptr;
		return std::unique_ptr<MatchingBase< double, 3> >( result );
	};
	
	const std::string& method = vm["method"].as<std::string>();
	const std::string& char_sequence = vm["char-sequence"].as<std::string>();
	
	std::unique_ptr<MatchingBase<double, 3> > match = create_match( method, char_sequence );
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

// stl
#include <map>
#include <memory>
#include <string>
#include <utility>

// boost
#include <boost/program_options.hpp>

// img2term
#include "img2term/img2term_colors.hxx"
#include "img2term/matching/matchingbase.hxx"
#include "img2term/matching/matchingrgbwithstate.hxx"

// img2term app
#include "img2term/app/register.hxx"
#include "img2term/app/typedefs.hxx"

namespace img2term
{
	namespace
	{
		class RegisterColor : Register<RegisterColor>
		{
		public:
			static std::string identifier();
			static MethodPair method();
		} registerColor;
		
		std::string RegisterColor::identifier()
		{
			return "color";
		}
		
		MethodPair RegisterColor::method()
		{
			auto factory = [] ( const bpo::variables_map& vm )
			{
				bool fg = vm["color-foreground"].as<bool>();
				bool bg = vm["color-background"].as<bool>();
				const auto& char_sequence = vm["char-sequence"].as<std::string>();
				int n_colors = vm["n-colors"].as<int>();
				auto result = n_colors == 8 ? 
				new MatchingRGBWithState<double, 3>( char_sequence, DefaultSelector<double, 3, 8>( fg, bg ) ) : n_colors == 16 ?
				new MatchingRGBWithState<double, 3>( char_sequence, DefaultSelector<double, 3, 16>( fg, bg ) ) :
				new MatchingRGBWithState<double, 3>( char_sequence, DefaultSelector<double, 3, 256>( fg, bg ) )
				;
				return MatchingPtr( result );
			}
			;
			
			Description desc_color = Description{ "color method options for --method=" + RegisterColor::identifier() };
			
			desc_color.add_options()
			( "char-sequence,c", bpo::value<std::string>()->default_value( "@" ), "Character sequence representing one pixel in color mode." 
			)
			( "color-background,b", bpo::value<bool>()->default_value( false ), "Paint background." )
			( "color-foreground,f", bpo::value<bool>()->default_value( true ),  "Paint foreground." )
			( "n-colors,n", bpo::value<int>()->default_value( 256 ), "Number of colors to be used (8,16,256)." )
			;
			
			return std::make_pair( factory, desc_color );
		}

	}
	
}
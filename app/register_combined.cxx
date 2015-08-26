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
#include "img2term/matching/matchinggrayscale.hxx"

// img2term app
#include "img2term/app/register.hxx"
#include "img2term/app/typedefs.hxx"

namespace img2term
{
	namespace
	{
		class RegisterCombined : Register<RegisterCombined>
		{
		public:
			static std::string identifier();
			static MethodPair method();
		} registerCombined;
		
		std::string RegisterCombined::identifier()
		{
			return "combined";
		}
		
		MethodPair RegisterCombined::method()
		{
			auto factory = [] ( const bpo::variables_map& vm )
			{
				bool fg = true;
				bool bg = false;
				const auto& char_sequence = vm["char-sequence"].as<std::string>();
				int n_colors = vm["n-colors"].as<int>();
				MatchingGrayScale<double, 3> gs{ &*std::begin( char_sequence ), &*std::end( char_sequence ) };
				auto func = [gs] ( const auto& patch ) { return gs.match( patch ); };
				auto result = n_colors == 8 ? 
				new MatchingRGBWithState<double, 3>( func, DefaultSelector<double, 3, 8>( fg, bg ) ) : n_colors == 16 ?
				new MatchingRGBWithState<double, 3>( func, DefaultSelector<double, 3, 16>( fg, bg ) ) :
				new MatchingRGBWithState<double, 3>( func, DefaultSelector<double, 3, 256>( fg, bg ) )
				;
				return MatchingPtr( result );
			}
			;
			
			Description desc_combined = Description{"combined method options for --method=" + RegisterCombined::identifier() };
			
			desc_combined.add_options()
			( "char-sequence,c", bpo::value<std::string>()->default_value( GRAYSCALE_DEFAULT ),
			  "Character sequence representing one pixel in color mode." )
			( "n-colors,n", bpo::value<int>()->default_value( 256 ), "Number of colors to be used (8,16,256)." )
			;
			
			return std::make_pair( factory, desc_combined );
		}
	}
	
}
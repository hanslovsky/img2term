// stl
#include <map>
#include <string>
#include <utility>

// boost
#include <boost/program_options.hpp>

// img2term
#include "img2term/img2term_colors.hxx"
#include "img2term/matching/matchingbase.hxx"
#include "img2term/matching/matchinggrayscale.hxx"

// img2term app
#include "img2term/app/register.hxx"
#include "img2term/app/typedefs.hxx"

namespace img2term
{
	namespace
	{
		class RegisterGrayscale : Register<RegisterGrayscale>
		{
		public:
			static std::string identifier();
			static MethodPair method();
		} registerGrayscale;
		
		std::string RegisterGrayscale::identifier()
		{
			return "grayscale";
		}
		
		MethodPair RegisterGrayscale::method()
		{
			Description desc_color = Description{ "grayscale method options for --method=" + RegisterGrayscale::identifier() };
			
			desc_color.add_options()
			( "char-sequence,c", bpo::value<std::string>()->default_value( GRAYSCALE_DEFAULT ),
				"Character sequence representing one pixel in color mode." )
			;
			auto factory = [] ( const bpo::variables_map& vm )
			{
				const auto& char_sequence = vm["char-sequence"].as<std::string>();
				return MatchingPtr( new MatchingGrayScale<double, 3>( &*std::begin( char_sequence ), &*std::end( char_sequence ) ) );
			}
			;
			return std::make_pair( factory, desc_color );
		}
	}
	
}
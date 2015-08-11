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
#include "img2term/matching/matchinggrayscale.hxx"

// img2term app
#include "img2term/app/typedefs.hxx"

namespace img2term
{
	void add_mapping( const std::string method, MethodPair method_pair );
	
	auto factory = [] ( const bpo::variables_map& vm )
	{
		const auto& char_sequence = vm["char-sequence"].as<std::string>();
		return MatchingPtr( new MatchingGrayScale<double, 3>( &*std::begin( char_sequence ), &*std::end( char_sequence ) ) );
	}
	;
	
	const std::string grayscale = "grayscale";
	
	void register_grayscale()
	{
		Description desc_color = Description( new bpo::options_description( "grayscale method options for --method=grayscale" ) );
		
		desc_color->add_options()
		( "char-sequence,c", bpo::value<std::string>()->default_value( GRAYSCALE_DEFAULT ),
		  "Character sequence representing one pixel in color mode." )
		;
		add_mapping( grayscale, std::move( std::make_pair( std::move( factory ), std::move( desc_color ) ) ) );
	}
	
}
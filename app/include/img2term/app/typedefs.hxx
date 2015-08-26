#ifndef IMG2TERM_IMG2TERM_APP_TYPEDEFSS_HXX
#define IMG2TERM_IMG2TERM_APP_TYPEDEFSS_HXX

// stl
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>

// boost
#include <boost/program_options.hpp>

// img2term
#include "img2term/matching/matchingbase.hxx"

namespace img2term
{
	namespace bpo = boost::program_options;
	
	typedef std::unique_ptr<MatchingBase<double,3> > MatchingPtr;
	
	typedef std::function<MatchingPtr( const bpo::variables_map& )> MatchingFactory;
	
	typedef bpo::options_description Description;
	
	typedef std::pair< MatchingFactory, Description > MethodPair;
}

#endif /* IMG2TERM_IMG2TERM_APP_TYPEDEFSS_HXX */
/*
 * Copyright (c) 2015 <copyright holder> <email>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef MATCHINGRGBWITHSTATE_H
#define MATCHINGRGBWITHSTATE_H

// stl
#include <functional>
#include <iterator>
#include <numeric>
#include <sstream>

// img2term
#include "img2term/img2term.hxx"
#include "img2term/img2term_colors.hxx"
#include "img2term/matching/matchingbase.hxx"

namespace img2term
{
	
	namespace
	{
		auto selector = [] ( auto pixel ) -> std::string 
		{
			double minimum_distance = std::numeric_limits< double >::max();
			int minimum_index = 0;
			for( auto c = std::begin( COLOR_256 ); c != std::end( COLOR_256 ); ++c )
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
			ss << "\033[38;05;" << minimum_index << "m";
			ss << "\033[48;05;" << minimum_index << "m";
			return ss.str();
		};
	}

	template <typename T, int SIZE>
	class MatchingRGBWithState : public MatchingBase<T, SIZE>
	{
	public:
		typedef std::function<std::string( const PixelType<T, SIZE>& )> SelectorType;
		typedef PixelType<T, SIZE> State;
		MatchingRGBWithState() = default;
		MatchingRGBWithState( const std::string& put_string );
		MatchingRGBWithState( SelectorType selector  );
		MatchingRGBWithState( const std::string& put_string, SelectorType selector  );
		MatchingRGBWithState( SelectorType put_string, SelectorType selector  );
		MatchingRGBWithState( State&& initial_state, SelectorType put_string, SelectorType selector );
		~MatchingRGBWithState() override = default;
		
		std::string match( const PixelType<T, SIZE>& patch ) const override;
		
	private:
		State state_ = State( -1, -1, -1 );
		const SelectorType put_string_ = [] ( PixelType<T, SIZE> ) -> std::string { return "@"; };
		const SelectorType selector_ = selector;
	};
}


namespace img2term
{
	template <typename T, int SIZE>
	MatchingRGBWithState<T, SIZE>::MatchingRGBWithState( const std::string& put_string ) :
	put_string_( [&put_string] ( PixelType<T, SIZE> ) { return put_string; } )
	{
		
	}
	
	template <typename T, int SIZE>
	MatchingRGBWithState<T, SIZE>::MatchingRGBWithState( SelectorType selector ) :
	selector_( selector )
	{
		
	}
	
	template <typename T, int SIZE>
	MatchingRGBWithState<T, SIZE>::MatchingRGBWithState( const std::string& put_string, SelectorType selector ) :
	put_string_( [&put_string] ( PixelType<T, SIZE> ) { return put_string; } ),
	selector_( selector )
	{
		
	}
	
	template <typename T, int SIZE>
	MatchingRGBWithState<T, SIZE>::MatchingRGBWithState( SelectorType put_string, SelectorType selector ) :
	put_string_( put_string ),
	selector_( selector )
	{

	}
	
	template <typename T, int SIZE>
	MatchingRGBWithState<T, SIZE>::MatchingRGBWithState( State&& initial_state, SelectorType put_string, SelectorType selector ) :
		state_( initial_state ),
		put_string_( put_string ),
		selector_( selector )
	{
			
	}
	
	template <typename T, int SIZE>
	std::string MatchingRGBWithState<T, SIZE>::match( const PixelType<T, SIZE>& patch ) const
	{
		std::stringstream ss;
		if ( patch != state_ )
		{
			ss << selector_( patch );
		}
		ss << put_string_( patch );
		return ss.str();
	}

}


#endif // MATCHINGRGBWITHSTATE_H

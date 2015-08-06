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

#ifndef MATCHINGGRAYSCALE_H
#define MATCHINGGRAYSCALE_H

// stl
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <string>

// img2term
#include "img2term/img2term.hxx"
#include "img2term/matching/matchingbase.hxx"

namespace img2term
{
	
	template <typename T, int SIZE>
	class MatchingGrayScale : MatchingBase<T, SIZE>
	{
	public:
		
// 		typedef std::iterator<std::random_access_iterator_tag, char> Iterator;
		
		static std::initializer_list<char> default_symbols;
		
		MatchingGrayScale();
		MatchingGrayScale( char const* begin, size_t size );
		MatchingGrayScale( char const* begin, char const* end );
// 		MatchingGrayScale( Iterator begin, Iterator end );
		~MatchingGrayScale() override = default;
		
		std::string match( const PixelType<T, SIZE>& patch ) const override;
		
	private:
		char const* begin_;
		const size_t size_;
	};

}


namespace img2term
{
	// IMPLEMENTATIONS
	
	template <typename T, int SIZE>
	std::initializer_list<char> MatchingGrayScale<T, SIZE>::default_symbols { ' ', '.', ',', '-', ':', '+', '&', '#', '@' };
	
	template <typename T, int SIZE>
	MatchingGrayScale<T, SIZE>::MatchingGrayScale() :
		MatchingGrayScale( std::begin( default_symbols ),
						   std::end( default_symbols ) )
	{

	}
	
	template <typename T, int SIZE>
	MatchingGrayScale<T, SIZE>::MatchingGrayScale( char const* begin, size_t size ) :
		begin_( begin ),
		size_( size )
	{
		
	}
	
	template <typename T, int SIZE>
	MatchingGrayScale<T, SIZE>::MatchingGrayScale( char const* begin, char const* end ) :
	MatchingGrayScale( begin, end - begin )
	{
		
	}
	
// 	template <typename T, int SIZE>
// 	MatchingGrayScale<T, SIZE>::MatchingGrayScale( Iterator begin, Iterator end ) :
// 		MatchingGrayScale( &*begin, &*end )
// 	{
// 		
// 	}

	template <typename T, int SIZE>
	std::string img2term::MatchingGrayScale<T, SIZE>::match ( const PixelType<T, SIZE>& pixel ) const
	{
		T index = std::accumulate( std::begin( pixel ), std::end( pixel ), 0 ) * this->size_ / ( SIZE * 255 );
		return std::string( 1, this->begin_[ (size_t)index ] );
	}
}


#endif // MATCHINGGRAYSCALE_H

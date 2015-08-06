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

#ifndef MATCHINGFUNCTOR_H
#define MATCHINGFUNCTOR_H

// stl
#include <functional>
#include <string>

// img2term
#include "img2term/img2term.hxx"
#include "img2term/matching/matchingbase.hxx"

namespace img2term
{

	template <typename T, int SIZE, typename FUNCTOR=std::function<std::string( const PixelType<T, SIZE> )> >
	class MatchingFunctor : public MatchingBase<T, SIZE>
	{
	public:
		MatchingFunctor() = delete;
		MatchingFunctor( FUNCTOR&& functor );
		~MatchingFunctor() override = default;
		std::string match( const PixelType<T, SIZE>& patch ) const override;
	private:
		FUNCTOR functor_;
	};
	
	


// IMPLEMENTATIONS
template <typename T, int SIZE, typename FUNCTOR>
MatchingFunctor<T, SIZE, FUNCTOR>::MatchingFunctor( FUNCTOR&& functor ) : functor_( std::move( functor ) )
{
	
}

template <typename T, int SIZE, typename FUNCTOR>
std::string img2term::MatchingFunctor<T, SIZE, FUNCTOR>::match ( const PixelType<T, SIZE>& patch ) const
{
	return functor_( patch );
}
}



#endif // MATCHINGFUNCTOR_H

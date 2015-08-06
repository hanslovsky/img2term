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

#ifndef AVERAGINGFUNCTOR_H
#define AVERAGINGFUNCTOR_H

// stl
#include <functional>

// img2term
#include "img2term/img2term.hxx"
#include "img2term/averaging/averagingbase.hxx"

namespace img2term
{

	template <typename T, typename U, int SIZE, typename FUNCTOR=std::function<void( const ImageView<T, SIZE>&, PixelType<U, SIZE>& )> >
	class AveragingFunctor : AveragingBase<T, U, SIZE>
	{
	public:
		AveragingFunctor() = delete;
		AveragingFunctor ( FUNCTOR&& functor );
		~AveragingFunctor() override = default;
		void operator() ( const ImageView< T, SIZE >& patch, PixelType<U, SIZE>& sum ) const override;
	private:
		FUNCTOR functor_;
		
	};
}


namespace img2term
{
	template <typename T, typename U, int SIZE, typename FUNCTOR>
	AveragingFunctor<T, U, SIZE, FUNCTOR>::AveragingFunctor( FUNCTOR&& functor ) : functor_( functor )
	{
		
	}
	
	template <typename T, typename U, int SIZE, typename FUNCTOR>
	void AveragingFunctor<T, U, SIZE, FUNCTOR>::operator() ( const ImageView< T, SIZE >& patch, PixelType<U, SIZE>& sum ) const
	{
		functor_( patch, sum );
	}
}

#endif // AVERAGINGFUNCTOR_H

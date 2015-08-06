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

#ifndef AVERAGINGMEAN_H
#define AVERAGINGMEAN_H

// img2term
#include "img2term/img2term.hxx"
#include "img2term/averaging/averagingbase.hxx"

namespace img2term
{
	
	template <typename T, typename U, int SIZE>
	class AveragingMean : AveragingBase<T, U, SIZE>
	{
	public:
		~AveragingMean() override = default;
		void operator() ( const ImageView< T, SIZE >& patch, PixelType<U, SIZE>& sum ) const override;
	};
}


namespace img2term
{
	template <typename T, typename U, int SIZE>
	void img2term::AveragingMean<T, U, SIZE>::operator() ( const ImageView<T, SIZE>& patch, PixelType< U, SIZE >& sum ) const
	{
		const double size = patch.end() - patch.begin();
		for ( const auto& val : patch )
		{
			sum += val;
		}
		sum /= size;
	}
}


#endif // AVERAGINGMEAN_H

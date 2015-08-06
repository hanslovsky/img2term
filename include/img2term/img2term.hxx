#pragma once

// vigra
#include <vigra/multi_array.hxx>
#include <vigra/tinyvector.hxx>


namespace img2term
{

	template <typename T, int SIZE>
	using PixelType = vigra::TinyVector<T, SIZE>;
	
	template <typename T, int SIZE>
	using Image = vigra::MultiArray<2, PixelType<T, SIZE> >;
	
	template <typename T, int SIZE>
	using ImageView = vigra::MultiArrayView<2, PixelType<T, SIZE> >;

}

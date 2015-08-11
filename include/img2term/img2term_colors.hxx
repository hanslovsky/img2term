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

#ifndef IMG2TERM_IMG2TERM_COLORS_HXX
#define IMG2TERM_IMG2TERM_COLORS_HXX

// stl
#include <initializer_list>

namespace img2term
{
	typedef unsigned int uint;
	
	extern std::initializer_list<char> GRAYSCALE_DEFAULT;
	
	typedef std::initializer_list< std::initializer_list< uint > > ColorList;
	
	extern ColorList COLOR_8;

	extern ColorList COLOR_16;

	extern ColorList COLOR_256;
	
	template <int COLORS>
	const ColorList& get_colors();
	
}


#endif /* IMG2TERM_IMG2TERM_COLORS_HXX */

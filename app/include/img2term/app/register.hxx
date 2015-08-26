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

#ifndef IMG2TERM_IMG2TERM_APP_REGISTER_H
#define IMG2TERM_IMG2TERM_APP_REGISTER_H

// stl
#include <map>
#include <string>

// img2term
#include "img2term/app/typedefs.hxx"

namespace img2term
{
	class RegisterManager
	{
	public:
		typedef std::map<std::string, MethodPair> MethodsAndOptions;
		static void registerMethod( std::string identifier, img2term::MethodPair method );
		static MethodsAndOptions getMethodsAndOptions();
	private:
		static MethodsAndOptions methodsAndOptions;
	};
	
	template <typename T>
	class Register
	{
	public:
		Register();
		static bool registered;
		static bool init();
	};
	
	template <typename T>
	Register<T>::Register()
	{
		(void)registered;
	}
	
	template <typename T>
	bool Register<T>::registered = init();
	
	template <typename T>
	bool Register<T>::init()
	{
		RegisterManager::registerMethod( T::identifier(), T::method() );
		return true;
	}
	
	
}

#endif /* IMG2TERM_IMG2TERM_APP_REGISTER_H */

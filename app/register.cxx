// stl
#include <map>
#include <string>
#include <utility>

// img2term
#include "img2term/app/register.hxx"

namespace img2term
{
	void RegisterManager::registerMethod( std::string identifier, MethodPair method )
	{
		methodsAndOptions.insert( std::make_pair( identifier, method ) );
	}
	
	RegisterManager::MethodsAndOptions RegisterManager::getMethodsAndOptions()
	{
		return methodsAndOptions;
	}
	
	RegisterManager::MethodsAndOptions RegisterManager::methodsAndOptions = MethodsAndOptions{};
}
#ifndef STRINGIFYING_HPP
#define STRINGIFYING_HPP

#include <string>
#include <typeinfo>
#include <cxxabi.h>

namespace cpputil
{

class Stringifyable
{
public:

	virtual std::string toString()
	{
		int status;
		char * demangled = abi::__cxa_demangle(typeid (*this).name(), 0, 0, &status);
		return std::string(demangled);
	}
};

}

#endif /* STRINGIFYING_HPP */


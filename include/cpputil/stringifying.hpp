/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef STRINGIFYING_HPP
#define STRINGIFYING_HPP

#include <string>
#include <typeinfo>
#include <cxxabi.h>

class Stringifyable
{
public:

	virtual std::string to_string()
	{
		int status;
		char * demangled = abi::__cxa_demangle(typeid (*this).name(), 0, 0, &status);
		return std::string(demangled);
	}
};

#endif /* STRINGIFYING_HPP */

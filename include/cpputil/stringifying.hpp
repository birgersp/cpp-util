/**
 * @author birgersp
 * https://github.com/birgersp
 */

#pragma once

#include <string>
#include <typeinfo>
#include <cxxabi.h>

class Stringifyable
{
public:

	virtual String to_string()
	{
		int status;
		char * demangled = abi::__cxa_demangle(typeid (*this).name(), 0, 0, &status);
		return String(demangled);
	}
};

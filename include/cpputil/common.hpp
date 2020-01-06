/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <vector>
#include <cpputil/core.hpp>

inline String get_function_name(String_ref function_header)
{
	int i0 = function_header.find(" ");
	int i1 = function_header.find("(");
	return function_header.substr(i0 + 1, i1 - i0 - 1);
}

#endif /* COMMON_HPP */

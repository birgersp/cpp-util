/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef PRINTING_H
#define PRINTING_H

#include <cpputil/core.hpp>
#include <cpputil/common.hpp>
#include <iostream>

inline std::string get_function_message(String_ref function_header, String_ref message)
{
	std::string result = get_function_name(function_header);
	result += ": \"" + message + "\"";
	return result;
}

template <typename T>
inline void print_line(T data)
{
	std::cout << data << std::endl;
}

inline void print_function(String_ref function_header, String_ref message)
{
	print_line(get_function_message(function_header, message));
}

inline void print_error_string(String_ref message)
{
	std::cerr << message << std::endl;
}

inline void print_function_error(String_ref function_header, String_ref message)
{
	print_error_string(get_function_message(function_header, message));
}

#endif /* PRINTING_H */

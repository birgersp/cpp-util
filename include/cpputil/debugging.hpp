/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef DEBUGGING_HPP
#define DEBUGGING_HPP

#include "printing.hpp"

#include "Source_code_origin.hpp"

inline void print_debug_info_message(const Source_code_origin source_origin, String_ref message)
{
	std::string result_string = get_source_origin_link_message
			(
			source_origin,
			"info",
			message.size() > 0 ? message : "(no info)");
	print_line(result_string);
}

inline void print_debug_info(const Source_code_origin source_origin)
{
	print_debug_info_message(source_origin, "");
}

inline void print_debug_info(const Source_code_origin source_origin, String_ref string)
{
	print_debug_info_message(source_origin, "\"" + string + "\"");
}

inline void print_debug_info(const Source_code_origin source_origin, const char* string)
{
	print_debug_info_message(source_origin, "\"" + std::string(string) + "\"");
}

inline void print_debug_info(const Source_code_origin source_origin, bool boolean)
{
	print_debug_info_message(source_origin, boolean ? "true" : "false");
}

inline void print_debug_info(const Source_code_origin source_origin, int number)
{
	print_debug_info_message(source_origin, std::to_string(number));
}

inline void print_debug_info(const Source_code_origin source_origin, unsigned int number)
{
	print_debug_info_message(source_origin, std::to_string(number));
}

inline void print_debug_info(const Source_code_origin source_origin, char character)
{
	print_debug_info_message(source_origin, std::string(1, character));
}

#define cpputil_debug_message(message) print_debug_info_message(get_source_origin(), message)
#define cpputil_debug_variable(variable) print_debug_info(get_source_origin(), variable)
#define cpputil_debug_function() print_debug_info(get_source_origin())


#endif /* DEBUGGING_HPP */


/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef SOURCE_CODE_ORIGIN_HPP
#define SOURCE_CODE_ORIGIN_HPP

#include "core.hpp"

struct Source_code_origin
{

	Source_code_origin()
	{
	}

	Source_code_origin(String function_header, String file_name, int line_number) :
	function_header(function_header), file_name(file_name), line_number(line_number)
	{
	}

	String function_header;
	String file_name;
	int line_number;
};

inline String get_source_origin_link_message(const Source_code_origin& source_origin, String_ref type, String_ref message)
{
	return "\t" + source_origin.file_name + ":" + std::to_string(source_origin.line_number) + ": " + type + ": " + message;
}

#define get_source_origin() Source_code_origin(__PRETTY_FUNCTION__, __FILE__, __LINE__)

#endif /* SOURCE_CODE_ORIGIN_HPP */

/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#include <cpputil/common.hpp>
#include <string>
#include <string.h>

#include "Source_code_origin.hpp"

class Exception
{
public:

	Exception(const Source_code_origin origin, const std::string reason) :
	origin(origin), reason(reason)
	{
	}

	Exception(const Source_code_origin origin, const Exception& parent) :
	Exception(origin, "Reason:\n" + parent.to_string())
	{
	}

	const Source_code_origin get_origin() const
	{
		return origin;
	}

	String_ref get_reason() const
	{
		return reason;
	}

	const std::string to_string() const
	{
		return get_source_origin_link_message(origin, "error", reason);
	}

private:

	const Source_code_origin origin;
	const std::string reason;

};

class Consequential_exception : public Exception
{
public:

	Consequential_exception(const Source_code_origin origin, const Exception& parent) :
	Exception(origin, parent), parent(parent)
	{
	}

private:

	const Exception& parent;

};

#define function_exception(reason) Exception(get_source_origin(), reason)
#define consequential_exception(cause) Consequential_exception(get_source_origin(), cause)
#define unsupported_function_exception() Exception(get_source_origin(), "Function not implemented")
#define function_error_exception() function_exception(strerror(errno))

#endif /* ERRORHANDLING_HPP */

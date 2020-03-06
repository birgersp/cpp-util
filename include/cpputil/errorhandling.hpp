/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#include <string>
#include <string.h>

#include "Source_code_origin.hpp"

class Exception
{
public:

	Exception(const Source_code_origin origin, String reason) :
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

	const String to_string() const
	{
		return get_source_origin_link_message(origin, "error", reason);
	}

private:

	const Source_code_origin origin;
	const String reason;

};

class Consequential_exception : public Exception
{
public:

	Consequential_exception(Source_code_origin origin, const Exception& parent) :
	Exception(origin, parent), parent(parent)
	{
	}

private:

	const Exception& parent;

};

inline String get_errno_string()
{
	return String(strerror(errno));
}

#define function_exception(reason) Exception(get_source_origin(), reason)
#define consequential_exception(cause) Consequential_exception(get_source_origin(), cause)
#define unsupported_function_exception() Exception(get_source_origin(), "Function not implemented")
#define function_error_exception() function_exception(get_errno_string())

#endif /* ERRORHANDLING_HPP */

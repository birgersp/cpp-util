#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#include <cpputil/common.hpp>
#include <string>
#include <string.h>

#include "SourceOrigin.hpp"

namespace cpputil
{

class Exception
{
public:

    Exception(const SourceOrigin origin, const std::string reason) :
    origin(origin), reason(reason)
    {
    }

    Exception(const SourceOrigin origin, const Exception& parent) :
    Exception(origin, parent.toString())
    {
    }

    const SourceOrigin getOrigin() const
    {
        return origin;
    }

    const std::string& getReason() const
    {
        return reason;
    }

    const std::string toString() const
    {
        return "Exception in \"" + cpputil::getFunctionName(origin.functionHeader) + "\" (" + origin.fileName + ": " + std::to_string(origin.lineNumber) + "). Reason:\n\t" + reason;
    }

private:

    const SourceOrigin origin;
    const std::string reason;

};

class ConsequentialException : public Exception
{
public:

    ConsequentialException(const SourceOrigin origin, const Exception& parent) :
    Exception(origin, parent), parent(parent)
    {
    }

private:

    const Exception& parent;

};

}

#define exceptionOrigin cpputil::SourceOrigin(__PRETTY_FUNCTION__, __FILE__, __LINE__)
#define functionException(reason) cpputil::Exception(exceptionOrigin, reason)
#define consequentialException(cause) cpputil::ConsequentialException(exceptionOrigin, cause)
#define unsupportedFunctionException() cpputil::Exception(exceptionOrigin, "Function not implemented")
#define functionErrorException() functionException(strerror(errno))

#endif /* ERRORHANDLING_HPP */

#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#include <cpputil/common.hpp>
#include <string>
#include <string.h>

namespace cpputil
{

struct ExceptionOrigin
{

    ExceptionOrigin()
    {
    }

    ExceptionOrigin(std::string functionHeader, std::string fileName, int lineNumber) :
    functionHeader(functionHeader), fileName(fileName), lineNumber(lineNumber)
    {
    }

    std::string functionHeader;
    std::string fileName;
    int lineNumber;
};

class Exception
{
public:

    Exception(const ExceptionOrigin origin, const std::string reason) :
    origin(origin), reason(reason)
    {
    }

    Exception(const ExceptionOrigin origin, const Exception& parent) :
    Exception(origin, parent.toString())
    {
    }

    const ExceptionOrigin getOrigin() const
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

    const ExceptionOrigin origin;
    const std::string reason;

};

class ConsequentialException : public Exception
{
public:

    ConsequentialException(const ExceptionOrigin origin, const Exception& parent) :
    Exception(origin, parent), parent(parent)
    {
    }

private:

    const Exception& parent;

};

}

#define exceptionOrigin cpputil::ExceptionOrigin(__PRETTY_FUNCTION__, __FILE__, __LINE__)
#define functionException(reason) cpputil::Exception(exceptionOrigin, reason)
#define consequentialException(cause) cpputil::ConsequentialException(exceptionOrigin, cause)
#define unsupportedFunctionException() cpputil::Exception(exceptionOrigin, "Function not implemented")
#define functionErrorException() functionException(strerror(errno))

#endif /* ERRORHANDLING_HPP */

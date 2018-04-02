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
    Exception(origin, "Reason:\n" + parent.toString())
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
        return getSourceOriginLinkMessage(origin, "error", reason);
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

#define functionException(reason) cpputil::Exception(getSourceOrigin(), reason)
#define consequentialException(cause) cpputil::ConsequentialException(getSourceOrigin(), cause)
#define unsupportedFunctionException() cpputil::Exception(getSourceOrigin(), "Function not implemented")
#define functionErrorException() functionException(strerror(errno))

#endif /* ERRORHANDLING_HPP */

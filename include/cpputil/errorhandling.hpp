#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#include <cpputil/common.hpp>
#include <string>
#include <string.h>

namespace cpputil
{

class Exception
{
public:

    Exception(const std::string& functionName, const std::string& filename, int line, const std::string& reason) :
    functionName(functionName), filename(filename), line(line), reason(reason)
    {
    }

    Exception(const std::string& functionName, const std::string& filename, int line, const Exception& parent) :
    Exception(functionName, filename, line, parent.toString())
    {
    }

    const std::string& getFunctionName() const
    {
        return functionName;
    }

    const std::string& getFilename() const
    {
        return filename;
    }

    int getLine() const
    {
        return line;
    }

    const std::string& getReason() const
    {
        return reason;
    }

    const std::string toString() const
    {
        return "Exception in \"" + cpputil::getFunctionName(functionName) + "\" (" + filename + ": " + std::to_string(line) + "). Reason:\n\t" + reason;
    }

private:

    const std::string functionName;
    const std::string filename;
    const int line;
    const std::string reason;

};

class ConsequentialException : public Exception
{
public:

    ConsequentialException(const std::string& functionName, const std::string& filename, int line, const Exception& parent) :
    Exception(functionName, filename, line, parent), parent(parent)
    {
    }

private:

    const Exception& parent;

};

}

#define functionException(reason) cpputil::Exception(__PRETTY_FUNCTION__, __FILE__, __LINE__, reason)
#define consequentialException(cause) cpputil::ConsequentialException(__PRETTY_FUNCTION__, __FILE__, __LINE__, cause)
#define unsupportedFunctionException() cpputil::Exception(__PRETTY_FUNCTION__, __FILE__, __LINE__, "Function not implemented")
#define functionErrorException() functionException(strerror(errno))

#endif /* ERRORHANDLING_HPP */

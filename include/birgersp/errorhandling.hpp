#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#define functionException(reason) birgersp::Exception(__PRETTY_FUNCTION__, __FILE__, __LINE__, reason)
#define consequentialException(cause) birgersp::ConsequentialException(__PRETTY_FUNCTION__, __FILE__, __LINE__, cause)

#include <birgersp/common.hpp>
#include <string>

namespace birgersp
{

class Exception
{
public:

    Exception(const std::string& function, const std::string& filename, int line, const std::string& reason) :
    function(function), filename(filename), line(line), reason(reason)
    {
    }

    Exception(const std::string& function, const std::string& filename, int line, const Exception& parent) :
    Exception(function, filename, line, parent.toString())
    {
    }

    const std::string toString() const
    {
        return "Exception in \"" + getFunctionName(function) + "\" (" + filename + ": " + std::to_string(line) + ")\nReason: " + reason;
    }

private:

    std::string function;
    std::string filename;
    int line;
    std::string reason;

};

class ConsequentialException : public Exception
{
public:

    ConsequentialException(const std::string& function, const std::string& filename, int line, const Exception& parent) :
    Exception(function, filename, line, parent), parent(parent)
    {
    }

private:

    const Exception& parent;

};

}

#endif /* ERRORHANDLING_HPP */

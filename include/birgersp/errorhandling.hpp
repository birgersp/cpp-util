#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#define functionException(reason) birgersp::Exception(__PRETTY_FUNCTION__, __FILE__, __LINE__, reason)
#define consequentialException(cause) birgersp::Exception(__PRETTY_FUNCTION__, __FILE__, __LINE__, cause)

#include <birgersp/common.hpp>
#include <string>

namespace birgersp
{

class Exception
{
public:

    Exception(const std::string& message) :
    message(message)
    {
    }

    Exception(const std::string& function, const std::string& filename, int line, const std::string& reason)
    {
        message += "Exception in \"" + getFunctionName(function) + "\" (" + filename + ": " + std::to_string(line) + ")\nReason: " + reason;
    }

    Exception(const std::string& function, const std::string& filename, int line, const Exception& cause) :
    Exception(function, filename, line, cause.getMessage())
    {
    };

    const std::string& getMessage() const
    {
        return message;
    }

private:

    std::string message;

};

}

#endif /* ERRORHANDLING_HPP */

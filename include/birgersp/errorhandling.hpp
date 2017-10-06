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
        return "Exception in \"" + birgersp::getFunctionName(functionName) + "\" (" + filename + ": " + std::to_string(line) + "). Reason:\n\t" + reason;
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

#endif /* ERRORHANDLING_HPP */

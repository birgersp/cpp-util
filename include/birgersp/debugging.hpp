#ifndef DEBUGGING_HPP
#define DEBUGGING_HPP

#include <birgersp/printing.hpp>

namespace birgersp
{

inline std::string getDebugInfo(const std::string& functionHeader, const std::string& fileName, int lineNumber)
{
    return getFunctionName(functionHeader) + ", " + fileName + ", " + std::to_string(lineNumber);
}

inline void printDebugInfo(const std::string& functionHeader, const std::string& fileName, int lineNumber)
{
    printString(getDebugInfo(functionHeader, fileName, lineNumber));
}

inline void printDebugInfo(const std::string& functionHeader, const std::string& fileName, int lineNumber, const std::string& message)
{
    std::string resultingMessage = getDebugInfo(functionHeader, fileName, lineNumber);
    if (message.size() > 0)
        resultingMessage += ":\t" + message;
    printString(resultingMessage);
}

}

#define debugString(string) birgersp::printDebugInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__, string)
#define debugMessage(message) debugString(message)
#define debugVariable(variable) debugMessage(std::to_string(variable))
#define debugFunction() birgersp::printDebugInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__)


#endif /* DEBUGGING_HPP */


#ifndef DEBUGGING_HPP
#define DEBUGGING_HPP

#include <cpputil/printing.hpp>

namespace cpputil
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

#define cpputilDebugString(string) cpputil::printDebugInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__, string)
#define cpputilDebugMessage(message) cpputilDebugString(message)
#define cpputilDebugVariable(variable) cpputilDebugMessage(std::to_string(variable))
#define cpputilDebugFunction() cpputil::printDebugInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__)


#endif /* DEBUGGING_HPP */


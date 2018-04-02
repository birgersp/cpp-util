#ifndef DEBUGGING_HPP
#define DEBUGGING_HPP

#include <cpputil/printing.hpp>

#include "SourceOrigin.hpp"

namespace cpputil
{

inline std::string getDebugInfo(const SourceOrigin sourceOrigin)
{
    return getFunctionName(sourceOrigin.functionHeader) + ", " + sourceOrigin.fileName + ", " + std::to_string(sourceOrigin.lineNumber);
}

inline void printDebugInfoMessage(const SourceOrigin sourceOrigin, const std::string& message)
{
    std::string resultString = getDebugInfo(sourceOrigin);
    resultString += ":\t" + message;
    printString(resultString);
}

inline void printDebugInfo(const SourceOrigin sourceOrigin)
{
    printString(getDebugInfo(sourceOrigin));
}

inline void printDebugInfo(const SourceOrigin sourceOrigin, const std::string& string)
{
    printDebugInfoMessage(sourceOrigin, "\"" + string + "\"");
}

inline void printDebugInfo(const SourceOrigin sourceOrigin, int number)
{
    printDebugInfoMessage(sourceOrigin, std::to_string(number));
}

inline void printDebugInfo(const SourceOrigin sourceOrigin, char character)
{
    printDebugInfoMessage(sourceOrigin, std::string(1, character));
}

}

#define cpputilDebugMessage(message) cpputil::printDebugInfoMessage(getSourceOrigin(), message)
#define cpputilDebugVariable(variable) cpputil::printDebugInfo(getSourceOrigin(), variable)
#define cpputilDebugFunction() cpputil::printDebugInfo(getSourceOrigin())


#endif /* DEBUGGING_HPP */


#ifndef DEBUGGING_HPP
#define DEBUGGING_HPP

#include <cpputil/printing.hpp>

#include "SourceOrigin.hpp"

namespace cpputil
{

inline void printDebugInfoMessage(const SourceOrigin sourceOrigin, const std::string& message)
{
    std::string resultString = getSourceOriginLinkMessage
            (
             sourceOrigin,
             "info",
             message.size() > 0 ? message : "(no info)");
    printString(resultString);
}

inline void printDebugInfo(const SourceOrigin sourceOrigin)
{
    printDebugInfoMessage(sourceOrigin, "");
}

inline void printDebugInfo(const SourceOrigin sourceOrigin, const std::string& string)
{
    printDebugInfoMessage(sourceOrigin, "\"" + string + "\"");
}

inline void printDebugInfo(const SourceOrigin sourceOrigin, bool boolean)
{
    printDebugInfoMessage(sourceOrigin, boolean ? "true" : "false");
}

inline void printDebugInfo(const SourceOrigin sourceOrigin, int number)
{
    printDebugInfoMessage(sourceOrigin, std::to_string(number));
}

inline void printDebugInfo(const SourceOrigin sourceOrigin, unsigned int number)
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


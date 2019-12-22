/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef DEBUGGING_HPP
#define DEBUGGING_HPP

#include <cpputil/printing.hpp>

#include "Source_code_origin.hpp"

namespace cpputil
{

inline void printDebugInfoMessage(const SourceCodeOrigin sourceOrigin, StringRef message)
{
	std::string resultString = getSourceOriginLinkMessage
			(
			sourceOrigin,
			"info",
			message.size() > 0 ? message : "(no info)");
	printLine(resultString);
}

inline void printDebugInfo(const SourceCodeOrigin sourceOrigin)
{
	printDebugInfoMessage(sourceOrigin, "");
}

inline void printDebugInfo(const SourceCodeOrigin sourceOrigin, StringRef string)
{
	printDebugInfoMessage(sourceOrigin, "\"" + string + "\"");
}

inline void printDebugInfo(const SourceCodeOrigin sourceOrigin, const char* string)
{
	printDebugInfoMessage(sourceOrigin, "\"" + std::string(string) + "\"");
}

inline void printDebugInfo(const SourceCodeOrigin sourceOrigin, bool boolean)
{
	printDebugInfoMessage(sourceOrigin, boolean ? "true" : "false");
}

inline void printDebugInfo(const SourceCodeOrigin sourceOrigin, int number)
{
	printDebugInfoMessage(sourceOrigin, std::to_string(number));
}

inline void printDebugInfo(const SourceCodeOrigin sourceOrigin, unsigned int number)
{
	printDebugInfoMessage(sourceOrigin, std::to_string(number));
}

inline void printDebugInfo(const SourceCodeOrigin sourceOrigin, char character)
{
	printDebugInfoMessage(sourceOrigin, std::string(1, character));
}

}

#define cpputilDebugMessage(message) cpputil::printDebugInfoMessage(getSourceOrigin(), message)
#define cpputilDebugVariable(variable) cpputil::printDebugInfo(getSourceOrigin(), variable)
#define cpputilDebugFunction() cpputil::printDebugInfo(getSourceOrigin())


#endif /* DEBUGGING_HPP */


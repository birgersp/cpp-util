/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef SOURCE_CODE_ORIGIN_HPP
#define SOURCE_CODE_ORIGIN_HPP

#include <cpputil/core.hpp>

namespace cpputil
{

struct SourceCodeOrigin
{

	SourceCodeOrigin()
	{
	}

	SourceCodeOrigin(std::string functionHeader, std::string fileName, int lineNumber) :
	functionHeader(functionHeader), fileName(fileName), lineNumber(lineNumber)
	{
	}

	std::string functionHeader;
	std::string fileName;
	int lineNumber;
};

inline std::string getSourceOriginLinkMessage(const SourceCodeOrigin& sourceOrigin, StringRef type, StringRef message)
{
	return "\t" + sourceOrigin.fileName + ":" + std::to_string(sourceOrigin.lineNumber) + ": " + type + ": " + message;
}

}

#define getSourceOrigin() cpputil::SourceCodeOrigin(__PRETTY_FUNCTION__, __FILE__, __LINE__)

#endif /* SOURCE_CODE_ORIGIN_HPP */

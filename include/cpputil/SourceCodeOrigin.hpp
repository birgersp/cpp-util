#ifndef SOURCECODEORIGIN_HPP
#define SOURCECODEORIGIN_HPP

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

#endif /* SOURCECODEORIGIN_HPP */

#ifndef SOURCEORIGIN_HPP
#define SOURCEORIGIN_HPP

#include <cpputil/core.hpp>

namespace cpputil
{

struct SourceOrigin
{

    SourceOrigin()
    {
    }

    SourceOrigin(std::string functionHeader, std::string fileName, int lineNumber) :
    functionHeader(functionHeader), fileName(fileName), lineNumber(lineNumber)
    {
    }

    std::string functionHeader;
    std::string fileName;
    int lineNumber;
};

inline std::string getSourceOriginLinkMessage(const SourceOrigin& sourceOrigin, StringRef type, StringRef message)
{
    return "\t" + sourceOrigin.fileName + ":" + std::to_string(sourceOrigin.lineNumber) + ": " + type + ": " + message;
}

}

#define getSourceOrigin() cpputil::SourceOrigin(__PRETTY_FUNCTION__, __FILE__, __LINE__)

#endif /* SOURCEORIGIN_HPP */

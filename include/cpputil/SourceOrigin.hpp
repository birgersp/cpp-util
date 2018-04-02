#ifndef SOURCEORIGIN_HPP
#define SOURCEORIGIN_HPP

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

inline std::string getSourceOriginLinkMessage(const SourceOrigin& sourceOrigin, const std::string& type, const std::string& message)
{
    return "\t" + sourceOrigin.fileName + ":" + std::to_string(sourceOrigin.lineNumber) + ": " + type + ": " + message;
}

}

#define getSourceOrigin() cpputil::SourceOrigin(__PRETTY_FUNCTION__, __FILE__, __LINE__)

#endif /* SOURCEORIGIN_HPP */

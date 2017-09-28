#ifndef DEBUGGING_HPP
#define DEBUGGING_HPP

#include "printing.hpp"

namespace birgersp
{

std::string getDebugInfo(const std::string& functionHeader, const std::string& fileName, int lineNumber)
{
    return getFunctionName(functionHeader) + ", " + fileName + ", " + std::to_string(lineNumber);
}

#define debugVariable(variable) birgersp::printString(birgersp::getDebugInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__) + ": " + std::to_string(variable))

}

#endif /* DEBUGGING_HPP */


#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <iostream>

#define log(message) birgersp::logFunction(__PRETTY_FUNCTION__, message)

namespace birgersp
{

namespace logging
{

std::string getFunctionName(const std::string& functionHeader)
{
    int i0 = functionHeader.find(" ");
    int i1 = functionHeader.find("(");
    return functionHeader.substr(i0 + 1, i1 - i0 - 1);
}

std::string toString(int integer)
{
    return std::to_string(integer);
}

void logFunction(const std::string& functionHeader, const std::string& message)
{
    std::string functionName = getFunctionName(functionHeader);
    std::cout << functionName << ": " << message << std::endl;
}

}

}

#endif /* LOGGING_H */


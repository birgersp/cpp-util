#ifndef LOGGING_H
#define LOGGING_H

#include "common.hpp"

#include <iostream>

#define log(message) birgersp::logging::logFunction(__PRETTY_FUNCTION__, message)

namespace birgersp
{

namespace logging
{

void logFunction(const std::string& functionHeader, const std::string& message)
{
    std::string functionName = getFunctionName(functionHeader);
    std::cout << functionName << ": " << message << std::endl;
}

}

}

#endif /* LOGGING_H */


#ifndef LOGGING_H
#define LOGGING_H

#include "common.hpp"

#include <iostream>

namespace birgersp
{

void logString(const std::string& message)
{
    std::cout << message << std::endl;
}

void logFunction(const std::string& functionHeader, const std::string& message)
{
    std::string functionName = getFunctionName(functionHeader);
    logString(functionName + ": " + message);
}

void logError(const std::string& message)
{
    std::cerr << message << std::endl;
}

}

#endif /* LOGGING_H */


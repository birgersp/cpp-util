#ifndef PRINTING_H
#define PRINTING_H

#include "common.hpp"

#include <iostream>

namespace birgersp
{

std::string getFunctionMessage(const std::string& functionHeader, const std::string& message)
{
    return getFunctionName(functionHeader) + ": " + message;
}

void printString(const std::string& string)
{
    std::cout << string << std::endl;
}

void printFunction(const std::string& functionHeader, const std::string& message)
{
    printString(getFunctionMessage(functionHeader, message));
}

void printErrorString(const std::string& message)
{
    std::cerr << message << std::endl;
}

void printFunctionError(const std::string& functionHeader, const std::string& message)
{
    printErrorString(getFunctionMessage(functionHeader, message));
}

}

#define print(message) printFunction(__PRETTY_FUNCTION__, message)
#define printError(message) printFunctionError(__PRETTY_FUNCTION__, message)

#endif /* PRINTING_H */

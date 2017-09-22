#ifndef PRINTING_H
#define PRINTING_H

#include <birgersp/common.hpp>

#include <iostream>

namespace birgersp
{

static std::string getFunctionMessage(const std::string& functionHeader, const std::string& message)
{
    std::string result = getFunctionName(functionHeader);
    result += ": \"" + message + "\"";
    return result;
}

static void printString(const std::string& string)
{
    std::cout << string << std::endl;
}

static void printFunction(const std::string& functionHeader, const std::string& message)
{
    printString(getFunctionMessage(functionHeader, message));
}

static void printErrorString(const std::string& message)
{
    std::cerr << message << std::endl;
}

static void printFunctionError(const std::string& functionHeader, const std::string& message)
{
    printErrorString(getFunctionMessage(functionHeader, message));
}

}

#define print(message) birgersp::printFunction(__PRETTY_FUNCTION__, message)
#define printError(message) birgersp::printFunctionError(__PRETTY_FUNCTION__, message)

#endif /* PRINTING_H */

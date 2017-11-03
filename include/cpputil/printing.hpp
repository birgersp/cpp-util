#ifndef PRINTING_H
#define PRINTING_H

#include <cpputil/common.hpp>
#include <iostream>

namespace cpputil
{

inline std::string getFunctionMessage(const std::string& functionHeader, const std::string& message)
{
    std::string result = getFunctionName(functionHeader);
    result += ": \"" + message + "\"";
    return result;
}

inline void printString(const std::string& string)
{
    std::cout << string << std::endl;
}

inline void printFunction(const std::string& functionHeader, const std::string& message)
{
    printString(getFunctionMessage(functionHeader, message));
}

inline void printErrorString(const std::string& message)
{
    std::cerr << message << std::endl;
}

inline void printFunctionError(const std::string& functionHeader, const std::string& message)
{
    printErrorString(getFunctionMessage(functionHeader, message));
}

}

#endif /* PRINTING_H */

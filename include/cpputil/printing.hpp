#ifndef PRINTING_H
#define PRINTING_H

#include <cpputil/core.hpp>
#include <cpputil/common.hpp>
#include <iostream>

namespace cpputil
{

inline std::string getFunctionMessage(StringRef functionHeader, StringRef message)
{
    std::string result = getFunctionName(functionHeader);
    result += ": \"" + message + "\"";
    return result;
}

inline void printString(StringRef string)
{
    std::cout << string << std::endl;
}

inline void printFunction(StringRef functionHeader, StringRef message)
{
    printString(getFunctionMessage(functionHeader, message));
}

inline void printErrorString(StringRef message)
{
    std::cerr << message << std::endl;
}

inline void printFunctionError(StringRef functionHeader, StringRef message)
{
    printErrorString(getFunctionMessage(functionHeader, message));
}

}

#endif /* PRINTING_H */

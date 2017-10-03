#ifndef PRINTING_H
#define PRINTING_H

#include <birgersp/common.hpp>
#include <iostream>

#include "observing.hpp"

namespace birgersp
{

typedef Observer<const std::string&> Logger;

class StandardOutputLogger : public Logger
{
public:

    virtual void notify(const std::string& string) override
    {
        std::cout << string << std::endl;
    }
};

static StandardOutputLogger _defaultLogger;
static Logger& _logger = _defaultLogger;

inline void setLogger(Logger& logger)
{
    _logger = logger;
}

inline std::string getFunctionMessage(const std::string& functionHeader, const std::string& message)
{
    std::string result = getFunctionName(functionHeader);
    result += ": \"" + message + "\"";
    return result;
}

inline void printString(const std::string& string)
{
    _logger.notify(string);
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

#define print(message) birgersp::printFunction(__PRETTY_FUNCTION__, message)
#define printError(message) birgersp::printFunctionError(__PRETTY_FUNCTION__, message)

#endif /* PRINTING_H */

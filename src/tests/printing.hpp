#ifndef TESTPRINTING_H
#define TESTPRINTING_H

#include <birgersp/printing.hpp>
#include <birgersp/testing.hpp>

using namespace birgersp;

namespace logging
{

class TestLogger : public Logger
{
public:

    void notify(const std::string& string)
    {
        loggedString = string;
    }

    std::string& getLoggedString()
    {
        return loggedString;
    }

private:

    std::string loggedString;

};

}

void testPrinting()
{
    logging::TestLogger testLogger;
    setLogger(testLogger);
    assertEquals("", testLogger.getLoggedString());
    birgersp::printString("hello");
    assertEquals("hello", testLogger.getLoggedString());
}

#endif /* TESTPRINTING_H */

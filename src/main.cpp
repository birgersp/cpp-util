#include <cpputil/testing.hpp>
#include <cpputil/debugging.hpp>

#include "consumer_test.h"
#include "string_test.h"
#include "stringifying_test.h"
#include "timing_test.h"

void demoDebugging()
{
    int x = 123;
    cpputilDebugVariable(x);
    cpputilDebugMessage("Hello hello");
    cpputilDebugFunction();
    cpputilDebugVariable('x');
}

void throwException()
{
    throw functionException("(ignore me)");
}

void throwConsequentialException()
{
    try
    {
        throwException();
    }
    catch (cpputil::Exception e)
    {
        throw consequentialException(e);
    }
}

void demoErrorHandling()
{
    try
    {
        throwException();
    }
    catch (cpputil::Exception e)
    {
        cpputil::printString(e.toString());
    }

    try
    {
        throwConsequentialException();
    }
    catch (cpputil::Exception e)
    {
        cpputil::printString(e.toString());
    }
}

bool performMiscTests()
{
    using namespace cpputil;
    using namespace tests;

    std::vector<TestFunction> miscFunctions = {
        testTiming,
        testConsumerProvider,
        testStringifying,
        testDebugging
    };
    return testAll(miscFunctions);
}

int main(int argc, char** argv)
{
    using namespace cpputil;
    using namespace tests;

    demoTests();

    std::vector<BoolFunction> testFunctions = {
        performMiscTests,
        testStringUtils
    };

    if (!allSucceed(testFunctions))
    {
        std::cerr << "Error: Some (actual) tests failed" << std::endl;
        return 1;
    }

    demoErrorHandling();

    return 0;
}

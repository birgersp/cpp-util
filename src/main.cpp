#include "tests/tests.h"

#include <cpputil/testing.hpp>

int main(int argc, char** argv)
{
    using namespace cpputil;
    using namespace tests;

    demoTests();

    std::vector<TestFunction> testFunctions = {
        testTiming,
        testConsumerProvider,
        testStringifying,
        testDebugging
    };

    if (!testAll(testFunctions))
        return 1;

    demoErrorHandling();

    return 0;
}

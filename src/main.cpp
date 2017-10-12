#include "tests/tests.h"

#include <birgersp/testing.hpp>

int main(int argc, char** argv)
{
    using namespace birgersp;
    using namespace tests;

    demoTests();

    std::vector<TestFunction> testFunctions = {
        testTiming,
        testObserving,
        testStringifying,
        testDebugging
    };

    testAll(testFunctions);

    demoErrorHandling();

    return 0;
}

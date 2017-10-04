#include <birgersp/testing.hpp>

#include "tests/testing.hpp"
#include "tests/timing.hpp"
#include "tests/observing.hpp"
#include "tests/stringifying.hpp"
#include "tests/debugging.hpp"
#include "tests/printing.hpp"

#include <birgersp/testing.hpp>

int main(int argc, char** argv)
{
    using namespace birgersp;

    demoTests();

    std::vector<TestFunction> testFunctions = {
        testTiming,
        testObserving,
        testStringifying,
        testDebugging,
        testPrinting
    };

    testAll(testFunctions);

    return 0;
}

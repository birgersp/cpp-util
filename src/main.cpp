#include "tests/testing.h"
#include "tests/timing.h"
#include "tests/observing.h"
#include "birgersp/testing.hpp"
#include "tests/stringifying.h"

int main(int argc, char** argv)
{
    demoTests();

    testStringifying();

    std::vector<birgersp::TestFunction> testFunctions = {
        testTiming,
        testObserving
    };
    return birgersp::testAll(testFunctions) ? 0 : 1;
}

#include "tests/testing.h"
#include "tests/timing.h"
#include "tests/observing.h"
#include "birgersp/testing.hpp"
#include "tests/stringifying.h"

#include <birgersp/testing.hpp>

int main(int argc, char** argv)
{
    using namespace birgersp;

    demoTests();

    std::vector<TestFunction> testFunctions = {
        testTiming,
        testObserving,
        testStringifying
    };

    testAll(testFunctions);

    return 0;
}

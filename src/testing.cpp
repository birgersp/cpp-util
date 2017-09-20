#include "birgersp/testing.hpp"

using namespace birgersp;

void test1()
{
    assertEquals(3, 2 + 1);
    assertTrue(1 + 1 == 2);
}

void test2()
{
    assertTrue(true);
    assertTrue(false);
}

void doSomeTests()
{
    std::vector<TestFunction> testFunctions = {
        test1,
        test2
    };

    logString("Performing tests");
    if (testAll(testFunctions))
    {
        logString("All tests succeeded");
    }
    else
    {
        logError("Error: Some tests failed");
    }
}

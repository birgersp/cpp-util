#include "birgersp/testing.hpp"

using namespace birgersp;

void dummyTest1()
{
    assertEquals(3, 2 + 1);
    assertTrue(1 + 1 == 2);
}

void dummyTest2()
{
    assertTrue(true);
    assertTrue(false);
}

void doSomeTests()
{
    std::vector<TestFunction> testFunctions = {
        dummyTest1,
        dummyTest2
    };

    printString("Performing tests");
    if (testAll(testFunctions))
    {
        printString("All tests succeeded");
    }
    else
    {
        printString("Error: Some tests failed");
    }
}

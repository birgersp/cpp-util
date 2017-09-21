#include <birgersp/testing.hpp>

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

void emptyTest()
{
}

void approximationTest()
{
    int x = 10;
    int y = 14;
    assertApproxEqual(x, y, 5);
}

void singleTest()
{
    assertTrue(true);
}

void demoTests()
{
    std::vector<TestFunction> testFunctions = {
        dummyTest1,
        dummyTest2,
        emptyTest,
        approximationTest
    };

    printString("(Ignore these test, they're supposed to fail)");
    testAll(testFunctions);
    test(singleTest);
}

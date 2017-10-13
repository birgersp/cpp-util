#include "tests.h"

#include <birgersp/testing.hpp>

namespace tests
{

void dummyTest1()
{
    assertEquals(3, 2 + 1);
    assertTrue(1 + 1 == 2);
    assertEquals(3, 2 + 2);
}

void dummyTest2()
{
    assertTrue(true);
    assertEquals("hei", "hade");
}

void dummyTest3()
{
    assertTrue(true);
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

void throwTestException()
{
    throw functionException("(dummy exception)");
}

void exceptionTest()
{
    registerTest();
    throwTestException();
    assertTrue(true);
}

void singleTest()
{
    assertTrue(true);
}

void demoTests()
{
    using namespace birgersp;

    std::vector<TestFunction> testFunctions = {
        dummyTest1,
        dummyTest2,
        dummyTest3,
        emptyTest,
        approximationTest,
        exceptionTest
    };

    testAll(testFunctions);
    test(singleTest);
}

}

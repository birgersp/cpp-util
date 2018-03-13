#include "tests.h"

#include <cpputil/testing.hpp>

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

void ambiguityTest()
{
    float x = 1.0;
    assertEquals((float) 1, x);
}

void demoTests()
{
    using namespace cpputil;

    std::vector<TestFunction> testFunctions = {
        dummyTest1,
        dummyTest2,
        dummyTest3,
        emptyTest,
        approximationTest,
        exceptionTest,
        ambiguityTest
    };

    testAll(testFunctions);
    test(singleTest);
}

}

#include <birgersp/timing.hpp>
#include <birgersp/testing.hpp>

#include <iostream>
#include <vector>
#include <windows.h>

using namespace birgersp;

void timerTest()
{
    Timer timer;

    Sleep(10);
    assertTrue(timer.elapsedMS() >= 10 && timer.elapsedMS() <= 11);

    timer.restart();
    assertEquals(0, timer.elapsedMS());
    Sleep(5);
    assertTrue(timer.elapsedMS() >= 5 && timer.elapsedMS() <= 6);
}

void testTiming()
{
    Timer timer;
    timer.elapsedMS();
    std::vector<TestFunction> tests = {
        timerTest
    };
    testAll(tests);
}

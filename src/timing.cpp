#include <birgersp/timing.hpp>
#include <birgersp/testing.hpp>

#include <iostream>
#include <vector>

using namespace birgersp;

void timerTest()
{
    Timer timer;

    sleepMS(10);
    assertTrue(timer.elapsedMS() >= 10 && timer.elapsedMS() <= 11);

    timer.restart();
    assertEquals(0, timer.elapsedMS());
    sleepMS(5);
    assertTrue(timer.elapsedMS() >= 5 && timer.elapsedMS() <= 6);
    assertTrue(timer.elapsedMS() > 0);
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

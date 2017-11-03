#include <birgersp/timing.hpp>
#include <birgersp/testing.hpp>

#include "tests.h"

namespace tests
{

void testTiming()
{
    using namespace cpputil;

    Timer timer;

    sleepMS(10);
    assertTrue(timer.elapsedMS() >= 10 && timer.elapsedMS() <= 11);

    timer.restart();
    assertEquals(0, timer.elapsedMS());
    sleepMS(5);
    assertTrue(timer.elapsedMS() >= 5 && timer.elapsedMS() <= 6);
    assertTrue(timer.elapsedMS() > 0);
}

}

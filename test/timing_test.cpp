#include <cpputil/timing.hpp>
#include <cpputil/testing.hpp>

namespace cpputil
{
namespace tests
{

void testTiming1()
{
    sleepMS(10);

    Timer timer;

    sleepMS(10);
    assertTrue(timer.elapsedMS() >= 10);
    assertTrue(timer.elapsedMS() <= 50);

    timer.restart();
    assertEquals(0, timer.elapsedMS());
    sleepMS(5);
    assertTrue(timer.elapsedMS() >= 5);
    assertTrue(timer.elapsedMS() <= 45);
    assertTrue(timer.elapsedMS() > 0);
}

bool testTiming()
{
    return test(testTiming1);
}

}
}

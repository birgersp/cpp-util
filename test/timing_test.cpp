#include <cpputil/timing.hpp>
#include <cpputil/testing.hpp>

namespace cpputil
{
namespace tests
{

void testTiming1()
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

bool testTiming()
{
    return test(testTiming1);
}

}
}

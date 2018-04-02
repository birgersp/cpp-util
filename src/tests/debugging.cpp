#include "tests.h"

#include <cpputil/testing.hpp>
#include <cpputil/debugging.hpp>

namespace tests
{

void testDebugging()
{
    int x = 123;
    cpputilDebugVariable(x);
    cpputilDebugMessage("Hello hello");
    cpputilDebugFunction();
    cpputilDebugVariable('x');
    assertTrue(true);
}

}

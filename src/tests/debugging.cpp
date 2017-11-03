#include "tests.h"

#include <birgersp/testing.hpp>
#include <birgersp/debugging.hpp>

namespace tests
{

void testDebugging()
{
    int x = 123;
    cpputilDebugVariable(x);
    cpputilDebugMessage("Hello hello");
    cpputilDebugFunction();
    assertTrue(true);
}

}

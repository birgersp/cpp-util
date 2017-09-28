#include "debugging.h"
#include "birgersp/testing.hpp"

#include <birgersp/debugging.hpp>

void testDebugging()
{
    int x = 123;
    debug(x);
    debug(0);
    debugFunction();
    assertTrue(true);
}

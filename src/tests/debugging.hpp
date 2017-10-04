#ifndef TESTDEBUGGING_H
#define TESTDEBUGGING_H

#include <birgersp/testing.hpp>
#include <birgersp/debugging.hpp>

void testDebugging()
{
    int x = 123;
    debugVariable(x);
    debugMessage("Hello hello");
    debugFunction();
    assertTrue(true);
}

#endif /* TESTDEBUGGING_H */

#ifndef TESTSTRINGIFYING_H
#define TESTSTRINGIFYING_H

#include <birgersp/testing.hpp>
#include <birgersp/stringifying.hpp>

namespace stringifying
{

class DummyClass : public birgersp::Stringifyable
{
};

}

void testStringifying()
{
    using namespace stringifying;

    DummyClass dc;
    assertEquals("stringifying::DummyClass", dc.toString());
}

#endif /* TESTSTRINGIFYING_H */

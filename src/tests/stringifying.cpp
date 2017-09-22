#include "stringifying.h"
#include "birgersp/testing.hpp"

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

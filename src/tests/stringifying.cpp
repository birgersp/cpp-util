#include "stringifying.h"
#include "birgersp/stringifying.hpp"
#include "birgersp/printing.hpp"

namespace stringifying
{

class DummyClass : public birgersp::Stringifiable
{
};

}

void testStringifying()
{
    stringifying::DummyClass dc;
    print(dc.toString());
}

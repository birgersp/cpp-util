#include <cpputil/testing.hpp>
#include <cpputil/stringifying.hpp>

namespace cpputil
{
namespace tests
{

namespace stringifying
{

class DummyClass : public cpputil::Stringifyable
{
};

}

void testStringifying1()
{
    using namespace stringifying;

    DummyClass dc;
    assertEquals("cpputil::tests::stringifying::DummyClass", dc.toString());
}

bool testStringifying()
{
    return test(testStringifying1);
}

}
}

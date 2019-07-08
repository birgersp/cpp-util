#include "core_test.h"
#include "cpputil/testing.hpp"

namespace cpputil
{
namespace tests
{

void testUlong()
{
	registerTest();
	unsigned long x = -1;
	ulong y = -1;
	assertTrue(x == y);
}

bool testCore()
{
	return test(testUlong);
}

}
}

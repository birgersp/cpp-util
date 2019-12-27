/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "core_test.h"
#include "cpputil/testing.hpp"

namespace cpputil
{
namespace tests
{

void test_ulong()
{
	register_test();
	unsigned long x = -1;
	ulong y = -1;
	assert_true(x == y);
}

bool test_core()
{
	return test(test_ulong);
}

}
}

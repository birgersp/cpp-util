/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include <cpputil/testing.hpp>
#include <cpputil/stringifying.hpp>

namespace cpputil
{
namespace tests
{

namespace stringifying
{

class Dummy_class : public cpputil::Stringifyable
{
};

}

void test_stringifying1()
{
	using namespace stringifying;

	Dummy_class dc;
	assert_equals("cpputil::tests::stringifying::Dummy_class", dc.to_string());
}

bool test_stringifying()
{
	return test(test_stringifying1);
}

}
}

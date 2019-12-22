#include "consumer_test.h"

#include <cpputil/testing.hpp>
#include <cpputil/Map.hpp>

namespace cpputil
{
namespace tests
{

using namespace cpputil;

void test_put_and_get()
{
	register_test();
	Map<std::string, std::string> map;
	map.put("hello", "world");
	assert_true(map.get("goodbye") == nullptr);
	assert_true(map.get("hello") != nullptr);
	assert_equals("world", *map.get("hello"));
}

void test_has()
{
	register_test();
	Map<std::string, std::string> map;
	assert_equals(false, map.has("hello"));
	map.put("hello", "world");
	assert_equals(true, map.has("hello"));
}

bool test_map()
{
	return test_all({
				test_put_and_get,
				test_has
	});
}

}
}

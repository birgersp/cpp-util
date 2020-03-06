/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "map_test.h"

#include <cpputil/testing.hpp>
#include <cpputil/Map.hpp>
#include <functional>

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

void test_foreach()
{
	register_test();
	Map<int, int> map;
	map.put(0, 0);
	int* v_ptr;
	v_ptr = map.get(0);
	assert_equals(0, *v_ptr);
	map.foreach([](const int& k, int& value)
	{
		if (k == 0)
		{
			value = 123;
		}
	});
	v_ptr = map.get(0);
	assert_equals(123, *v_ptr);
}

bool test_map()
{
	return test_all({
					test_put_and_get,
					test_has,
					test_foreach
	});
}

}
}

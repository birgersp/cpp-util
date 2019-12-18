#include "consumer_test.h"

#include <cpputil/testing.hpp>
#include <cpputil/Map.hpp>

namespace cpputil
{
namespace tests
{

using namespace cpputil;

void testPutAndGet()
{
	registerTest();
	Map<std::string, std::string> map;
	map.put("hello", "world");
	assertTrue(map.get("goodbye") == nullptr);
	assertTrue(map.get("hello") != nullptr);
	assertEquals("world", *map.get("hello"));
}

void testHas()
{
	registerTest();
	Map<std::string, std::string> map;
	assertEquals(false, map.has("hello"));
	map.put("hello", "world");
	assertEquals(true, map.has("hello"));
}

bool testMap()
{
	return testAll({
				testPutAndGet,
				testHas
	});
}

}
}

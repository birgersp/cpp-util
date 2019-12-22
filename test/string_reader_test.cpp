#include <cpputil/timing.hpp>
#include <cpputil/testing.hpp>

#include "cpputil/String_reader.hpp"

namespace cpputil
{
namespace tests
{
namespace string_reader
{

void test_String_reader()
{
	register_test();
	String_reader string_reader("Hello world");
	assert_equals(false, string_reader.at_end());
	String_reader::Result result;
	result = string_reader.read_until({' '});
	assert_equals("Hello", result.string);
	assert_equals(' ', result.leading_character);
	assert_equals(false, string_reader.at_end());
	result = string_reader.read_until({' '});
	assert_equals("world", result.string);
	assert_equals('\0', result.leading_character);
	assert_equals(true, string_reader.at_end());
	result = string_reader.read_until({' '});
	assert_equals("", result.string);
	assert_equals('\0', result.leading_character);
	assert_equals(true, string_reader.at_end());
}

}

bool test_String_reader()
{
	return test_all({
					string_reader::test_String_reader
	});
}

}
}

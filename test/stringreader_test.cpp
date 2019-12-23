/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include <cpputil/timing.hpp>
#include <cpputil/testing.hpp>

#include "cpputil/Stringreader.hpp"

namespace cpputil
{
namespace tests
{
namespace stringreader
{

void test_Stringreader()
{
	register_test();
	Stringreader string_reader("Hello world");
	assert_equals(false, string_reader.at_end());
	Stringreader::Result result;
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

bool test_Stringreader()
{
	return test_all({
					stringreader::test_Stringreader
	});
}

}
}

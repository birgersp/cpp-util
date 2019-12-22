/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include <cpputil/testing.hpp>
#include <cpputil/string.hpp>

namespace cpputil
{
namespace tests
{

void test_split_string()
{
	register_test();
	std::string subject =
			"first line\n"
			"second line\n"
			"third line\n"
			""
			;
	std::vector<std::string> result = split_string(subject, '\n');

	assert_equals(4, result.size());
	assert_equals("first line", result[0]);
	assert_equals("second line", result[1]);
	assert_equals("third line", result[2]);
	assert_equals("", result[3]);
}

void test_split_empty_string()
{
	register_test();
	std::vector<std::string> result = split_string("", '\n');
	assert_equals(0, result.size());
}

void test_to_lower_case()
{
	register_test();
	std::string subject = "Hello World!";
	to_lower_case(subject);
	assert_equals("hello world!", subject);
}

bool test_string_utils()
{
	std::vector<Test_function> tests = {
		test_split_string,
		test_split_empty_string,
		test_to_lower_case
	};

	return test_all(tests);
}

}
}

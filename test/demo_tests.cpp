#include <cpputil/testing.hpp>

namespace cpputil
{
namespace demo
{

void dummy_test1()
{
	assert_equals(3, 2 + 1);
	assert_true(1 + 1 == 2);
	assert_equals(3, 2 + 2);
}

void dummy_test2()
{
	assert_true(true);
	assert_equals("hei", "hade");
}

void dummy_test3()
{
	assert_true(true);
}

void dummy_test4()
{
	assert_true(false);
}

void empty_test()
{
}

void approximation_test()
{
	int x = 10;
	int y = 14;
	assert_approx_equal(x, y, 5);
}

void throw_test_exception()
{
	throw function_exception("(dummy exception)");
}

void exception_test()
{
	register_test();
	throw_test_exception();
	assert_true(true);
}

void single_test()
{
	assert_true(true);
}

void ambiguity_test()
{
	float x = 1.0;
	assert_equals((float) 1, x);
}

void bool_equals_test()
{
	assert_equals(true, false);
}

void disabled_test()
{
	assert_true(true);
	disable_test();
}

void empty_registered_test()
{
	register_test();
}

void char_equals_test()
{
	assert_equals('x', 'y');
}

void string_equals_test_should_fail()
{
	assert_equals("hello", "world");
}

void demo_tests()
{
	using namespace cpputil;

	std::vector<Test_function> test_functions = {
		dummy_test1,
		dummy_test2,
		dummy_test3,
		dummy_test4,
		empty_test,
		approximation_test,
		exception_test,
		ambiguity_test,
		bool_equals_test,
		disabled_test,
		empty_registered_test,
		char_equals_test,
		string_equals_test_should_fail
	};

	test_all(test_functions);
	test(single_test);
}

}
}

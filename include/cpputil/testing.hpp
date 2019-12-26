/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef TESTING_HPP
#define TESTING_HPP

#include <cpputil/core.hpp>
#include <cpputil/common.hpp>
#include <cpputil/printing.hpp>
#include <cpputil/errorhandling.hpp>
#include <cpputil/string.hpp>

#include <vector>
#include <string>

typedef void (*Test_function) (void);
typedef bool (*Bool_function) (void);

namespace testing
{

class Test_failed : public Exception
{
public:

	Test_failed(const Source_code_origin& origin, String_ref info) :
	Exception(origin, info)
	{
	}
};

class Comparison_test_failed : public Test_failed
{
public:

	Comparison_test_failed(const Source_code_origin& origin, String_ref expected, String_ref actual) :
	Test_failed(origin, generate_reason(expected, actual))
	{
	}

	Comparison_test_failed(const Source_code_origin& origin, String_ref expected, String_ref actual, const stringcompare::String_difference& difference) :
	Test_failed(origin, generate_reason(expected, actual, difference))
	{
	}

private:

	static std::string generate_reason(String_ref expected, String_ref actual)
	{
		return "Comparison failed\n\tExpected: " + expected + "\tActual: " + actual;
	}

	static std::string generate_reason(String_ref expected, String_ref actual, const stringcompare::String_difference& difference)
	{
		bool any_newlines = ((expected.find("\n") != -1) || (actual.find("\n") != -1));
		std::string message;
		if (any_newlines)
		{
			message = "Comparison failed\n\tExpected:\n" + expected + "\n\tActual:\n" + actual;
			message += "\n\t(Line " + std::to_string(difference.line) + ") " + difference.string1_line + " | " + difference.string2_line;
		}
		else
			message = "Comparison failed\n\tExpected: " + expected + "\tActual: " + actual;
		return message;
	}
};

class Tester
{
public:

	Tester()
	{
		clear_last_test();
	}

	void register_test(Source_code_origin source_origin)
	{
		set_last_test_origin(source_origin);
		last_test_state = Test_state::NO_ASSERTIONS;
	}

	void make_assertion(bool expression, Source_code_origin source_origin)
	{
		set_last_test_origin(source_origin);
		if (!expression)
			throw Test_failed(last_test_origin, "Assertion failed");
	}

	void make_equals_assertion(float expected, float actual, float delta, Source_code_origin source_origin)
	{
		set_last_test_origin(source_origin);
		float min = actual - delta;
		float max = actual + delta;
		if (expected < min || expected > max)
			throw Comparison_test_failed(last_test_origin, std::to_string(expected), std::to_string(actual));
	}

	void make_equals_assertion(float expected, float actual, Source_code_origin source_origin)
	{
		make_equals_assertion(expected, actual, 0, source_origin);
	}

	void make_equals_assertion(int expected, int actual, Source_code_origin source_origin)
	{
		set_last_test_origin(source_origin);
		if (expected != actual)
			throw Comparison_test_failed(last_test_origin, std::to_string(expected), std::to_string(actual));
	}

	void make_equals_assertion(unsigned int expected, unsigned int actual, Source_code_origin source_origin)
	{
		set_last_test_origin(source_origin);
		if (expected != actual)
			throw Comparison_test_failed(last_test_origin, std::to_string(expected), std::to_string(actual));
	}

	void make_equals_assertion(String_ref expected, String_ref actual, Source_code_origin source_origin)
	{
		set_last_test_origin(source_origin);
		stringcompare::String_difference difference;
		if (stringcompare::find_string_difference(expected, actual, difference))
			throw Comparison_test_failed(last_test_origin, "\"" + expected + "\"", "\"" + actual + "\"", difference);
	}

	void make_equals_assertion(const char* expected, const char* actual, Source_code_origin source_origin)
	{
		make_equals_assertion(std::string(expected), std::string(actual), source_origin);
	}

	void make_equals_assertion(bool expected, bool actual, Source_code_origin source_origin)
	{
		set_last_test_origin(source_origin);
		if (expected != actual)
			throw Comparison_test_failed(last_test_origin, bool_to_string(expected), bool_to_string(actual));
	}

	void make_equals_assertion(char expected, char actual, Source_code_origin source_origin)
	{
		set_last_test_origin(source_origin);
		if (expected != actual)
			throw Comparison_test_failed(last_test_origin, std::string(1, expected), std::string(1, actual));
	}

	void perform_test(Test_function function)
	{
		try
		{
			clear_last_test();
			function();
			if (last_test_state == Test_state::NOT_PASSED)
				last_test_state = Test_state::PASSED;
		}
		catch (Test_failed e)
		{
			last_test_origin = e.get_origin();
			last_test_message = e.get_reason();
		}
		catch (Exception e)
		{
			last_test_message = e.to_string();
			if (last_test_state != Test_state::DISABLED)
				last_test_state = Test_state::NOT_PASSED;
		}
	}

	bool test(Test_function function)
	{
		perform_test(function);

		bool passed;

		std::string status_string, header_string;

		if (last_test_state == Test_state::NO_ASSERTIONS)
		{
			status_string = "INVALID";
			passed = false;
		}
		else if (last_test_state == Test_state::PASSED)
		{
			status_string = "OK";
			passed = true;
		}
		else if (last_test_state == Test_state::NOT_PASSED)
		{
			status_string = "FAILED";
			passed = false;
		}
		else if (last_test_state == Test_state::DISABLED)
		{
			status_string = "IGNORED";
			passed = true;
		}

		if (has_test_origin)
			header_string = last_test_origin.function_header;
		else
			header_string = "(UNKNOWN TEST - NO ASSERTIONS)";

		std::string output_string;
		output_string += status_string;
		output_string += "\t";
		output_string += header_string;

		if (!passed && has_test_origin)
			output_string += "\n" + get_source_origin_link_message(last_test_origin, "error", "Test failed");

		if (last_test_message.size() > 0)
			output_string += "\n\tReason: " + last_test_message;

		print_line(output_string);
		return passed;
	}

	bool test_all(const std::vector<Test_function>& functions)
	{
		bool all_tests_succeeded = true;
		for (Test_function function : functions)
		{
			if (!test(function))
				all_tests_succeeded = false;
		}
		return all_tests_succeeded;
	}

	void disable_test(Source_code_origin source_origin)
	{
		set_last_test_origin(source_origin);
		last_test_state = Test_state::DISABLED;
		throw Exception(last_test_origin, "Test disabled");
	}

private:

	enum class Test_state
	{
		PASSED,
		NOT_PASSED,
		DISABLED,
		NO_ASSERTIONS
	} last_test_state;

	Source_code_origin last_test_origin;
	std::string last_test_message;
	bool has_test_origin;

	std::string bool_to_string(bool value)
	{
		return value ? "true" : "false";
	}

	void clear_last_test()
	{
		last_test_message = "";
		last_test_state = Test_state::NO_ASSERTIONS;
		has_test_origin = false;
	}

	void set_last_test_origin(Source_code_origin origin)
	{
		last_test_origin = origin;
		last_test_message = "";
		last_test_state = Test_state::NOT_PASSED;
		has_test_origin = true;
	}
};

static Tester _tester;

inline Tester& get_tester()
{
	return _tester;
}

}

inline bool test(Test_function function)
{
	print_line("Performing 1 test");
	bool result = testing::get_tester().test(function);
	print_line("");
	return result;
}

inline bool test_all(const std::vector<Test_function>& functions)
{
	if (functions.size() == 1)
		return test(functions[0]);
	else
	{
		print_line("Performing " + std::to_string(functions.size()) + " tests");
		bool result = testing::get_tester().test_all(functions);
		print_line("");
		return result;
	}
}

inline bool all_succeed(const std::vector<Bool_function>& bool_functions)
{
	bool success = true;
	for (auto function : bool_functions)
		if (!function())
			success = false;
	return success;
}

#define cpp_util_get_source_origin() Source_code_origin(__PRETTY_FUNCTION__, __FILE__, __LINE__)
#define register_test() testing::get_tester().register_test(cpp_util_get_source_origin())
#define assert_true(expression) testing::get_tester().make_assertion(expression, cpp_util_get_source_origin())
#define assert_approx_equal(expected, actual, delta) testing::get_tester().make_equals_assertion(expected, actual, delta, cpp_util_get_source_origin())
#define assert_equals(expected, actual) testing::get_tester().make_equals_assertion(expected, actual, cpp_util_get_source_origin())
#define disable_test() testing::get_tester().disable_test(cpp_util_get_source_origin())

#endif /* TESTING_HPP */

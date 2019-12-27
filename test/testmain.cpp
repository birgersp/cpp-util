/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include <iostream>

#include <vector>
#include <cpputil/testing.hpp>

#include "demo_tests.h"

#include "core_test.h"
#include "consumer_test.h"
#include "string_test.h"
#include "stringifying_test.h"
#include "timing_test.h"
#include "map_test.h"
#include "stringreader_test.h"
#include "table_printer_test.h"

int main(int argc, char** argv)
{
	using namespace cpputil;

	print_line("Demo testing");
	demo::demo_tests();

	print_line("Performing actual tests");
	std::vector<Bool_function> test_functions = {
		tests::test_core,
		tests::test_consumer,
		tests::test_string_utils,
		tests::test_stringifying,
		tests::test_timing,
		tests::test_map,
		tests::test_Stringreader,
		tests::test_table_printer
	};

	if (all_succeed(test_functions))
	{
		print_line("All (real) tests succeeded");
		return 0;
	}

	return 1;
}

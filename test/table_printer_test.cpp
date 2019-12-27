/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "table_printer_test.h"
#include <cpputil/Table_printer.h>
#include <cpputil/testing.hpp>

namespace cpputil
{
namespace tests
{
namespace table_printer
{

void test_table_printer()
{
	register_test();
	Table_printer table_printer;
	table_printer.add_row({"hey", "there"});
	assert_equals("hey there", table_printer.to_string());
	table_printer.add_row({"goodbye", "buddy"});
	assert_equals("hey     there\ngoodbye buddy", table_printer.to_string());
}
}

bool test_table_printer()
{
	return test_all({
					table_printer::test_table_printer
	});
}

}
}

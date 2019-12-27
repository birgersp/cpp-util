/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include <cpputil/timing.hpp>
#include <cpputil/testing.hpp>

namespace cpputil
{
namespace tests
{

void test_timing1()
{
	sleep_mS(10);

	Timer timer;

	sleep_mS(10);
	assert_true(timer.elapsed_mS() >= 10);
	assert_true(timer.elapsed_mS() <= 50);

	timer.restart();
	assert_equals(0, timer.elapsed_mS());
	sleep_mS(5);
	assert_true(timer.elapsed_mS() >= 5);
	assert_true(timer.elapsed_mS() <= 45);
	assert_true(timer.elapsed_mS() > 0);
}

bool test_timing()
{
	return test(test_timing1);
}

}
}

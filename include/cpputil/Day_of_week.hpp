/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef DAY_OF_WEEK_HPP
#define DAY_OF_WEEK_HPP

#include <map>
#include <string>

namespace cpputil
{

enum class DayOfWeek
{
	SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
};

const std::map<DayOfWeek, std::string> dayOfWeekNames = {
	{DayOfWeek::SUNDAY, "sunday"},
	{DayOfWeek::MONDAY, "monday"},
	{DayOfWeek::TUESDAY, "tuesday"},
	{DayOfWeek::WEDNESDAY, "wednesday"},
	{DayOfWeek::THURSDAY, "thursday"},
	{DayOfWeek::FRIDAY, "friday"},
	{DayOfWeek::SATURDAY, "saturday"}
};

const std::map<DayOfWeek, uint> dayOfWeekIndices = {
	{DayOfWeek::SUNDAY, 0},
	{DayOfWeek::MONDAY, 1},
	{DayOfWeek::TUESDAY, 2},
	{DayOfWeek::WEDNESDAY, 3},
	{DayOfWeek::THURSDAY, 4},
	{DayOfWeek::FRIDAY, 5},
	{DayOfWeek::SATURDAY, 6}
};

}

#endif /* DAY_OF_WEEK_HPP */


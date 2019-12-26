/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef DAY_OF_WEEK_HPP
#define DAY_OF_WEEK_HPP

#include <map>
#include <string>
#include <cpputil/core.hpp>

enum class Day_of_week
{
	SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
};

const std::map<Day_of_week, std::string> day_of_week_names = {
	{Day_of_week::SUNDAY, "sunday"},
	{Day_of_week::MONDAY, "monday"},
	{Day_of_week::TUESDAY, "tuesday"},
	{Day_of_week::WEDNESDAY, "wednesday"},
	{Day_of_week::THURSDAY, "thursday"},
	{Day_of_week::FRIDAY, "friday"},
	{Day_of_week::SATURDAY, "saturday"}
};

const std::map<Day_of_week, uint> day_of_week_indices = {
	{Day_of_week::SUNDAY, 0},
	{Day_of_week::MONDAY, 1},
	{Day_of_week::TUESDAY, 2},
	{Day_of_week::WEDNESDAY, 3},
	{Day_of_week::THURSDAY, 4},
	{Day_of_week::FRIDAY, 5},
	{Day_of_week::SATURDAY, 6}
};

#endif /* DAY_OF_WEEK_HPP */


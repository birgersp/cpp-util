#ifndef DAYOFWEEK_HPP
#define DAYOFWEEK_HPP

#include <map>
#include <string>

namespace cpputil
{

enum class DayOfWeek
{
    MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
};

const std::map<DayOfWeek, std::string> dayOfWeekNames = {
    {DayOfWeek::MONDAY, "monday"},
    {DayOfWeek::TUESDAY, "tuesday"},
    {DayOfWeek::WEDNESDAY, "wednesday"},
    {DayOfWeek::THURSDAY, "thursday"},
    {DayOfWeek::FRIDAY, "friday"},
    {DayOfWeek::SATURDAY, "saturday"},
    {DayOfWeek::SUNDAY, "sunday"}
};

const std::map<DayOfWeek, uint> dayOfWeekIndices = {
    {DayOfWeek::MONDAY, 1},
    {DayOfWeek::TUESDAY, 2},
    {DayOfWeek::WEDNESDAY, 3},
    {DayOfWeek::THURSDAY, 4},
    {DayOfWeek::FRIDAY, 5},
    {DayOfWeek::SATURDAY, 6},
    {DayOfWeek::SUNDAY, 7}
};

}

#endif /* DAYOFWEEK_HPP */


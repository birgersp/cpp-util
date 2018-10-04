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

}

#endif /* DAYOFWEEK_HPP */


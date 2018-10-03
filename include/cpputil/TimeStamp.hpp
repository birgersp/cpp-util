#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include <map>
#include <sys/time.h>
#include <cpputil/core.hpp>

namespace cpputil
{

inline ulong getCurrentSecondsSinceEpoch()
{
    timeval timeValue;
    gettimeofday(&timeValue, 0);
    time_t timeValueSeconds = timeValue.tv_sec;
    ulong secondsSinceEpoch = (ulong) timeValueSeconds;
    return secondsSinceEpoch;
}

const std::map<uint, std::string> weekDayNames =
{
    {1, "monday"},
    {2, "tuesday"},
    {3, "wednesday"},
    {4, "thursday"},
    {5, "friday"},
    {6, "saturday"},
    {7, "sunday"}
};

class Timestamp
{
public:

    Timestamp(ulong secondsSinceEpoch) :
    secondsSinceEpoch(secondsSinceEpoch)
    {
        time_t secondsSinceEpochInt = (time_t) secondsSinceEpoch;
        tm* values = localtime(&secondsSinceEpochInt);
        year = values->tm_year + 1900;
        month = values->tm_mon + 1;
        day = values->tm_mday;
        hour = values->tm_hour;
        minute = values->tm_min;
        second = values->tm_sec;
    }

    Timestamp() :
    Timestamp(getCurrentSecondsSinceEpoch())
    {
    }

    uint getDay() const
    {
        return day;
    }

    uint getHour() const
    {
        return hour;
    }

    uint getMinute() const
    {
        return minute;
    }

    uint getMonth() const
    {
        return month;
    }

    uint getSecond() const
    {
        return second;
    }

    ulong getSecondsSinceEpoch() const
    {
        return secondsSinceEpoch;
    }

    uint getYear() const
    {
        return year;
    }

    StringRef getWeekDayName() const
    {
        auto iterator = weekDayNames.find(day);
        return iterator->second;
    }

private:

    ulong secondsSinceEpoch;
    uint year, month, day, hour, minute, second;

};

}

#endif /* TIMESTAMP_HPP */

#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include <sys/time.h>
#include <cpputil/core.hpp>

namespace cpputil
{

class Timestamp
{
public:

    Timestamp()
    {
        timeval timeValue;
        gettimeofday(&timeValue, 0);
        time_t timeValueSeconds = timeValue.tv_sec;
        tm* values = localtime(&timeValueSeconds);

        secondsSinceEpoch = (ulong) timeValueSeconds;

        year = values->tm_year + 1900;
        month = values->tm_mon + 1;
        day = values->tm_mday;
        hour = values->tm_hour;
        minute = values->tm_min;
        second = values->tm_sec;
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

private:

    ulong secondsSinceEpoch;
    uint year, month, day, hour, minute, second;

};

}

#endif /* TIMESTAMP_HPP */

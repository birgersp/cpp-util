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
        gettimeofday(&timeValue, 0);
        timeValueSeconds = timeValue.tv_sec;
        values = localtime(&timeValueSeconds);
    }

    const int year() const
    {
        return values->tm_year + 1900;
    }

    const int month() const
    {
        return values->tm_mon + 1;
    }

    const int day() const
    {
        return values->tm_mday;
    }

    const int hour() const
    {
        return values->tm_hour;
    }

    const int minute() const
    {
        return values->tm_min;
    }

    const ulong secondsSinceEpoch() const
    {
        return timeValueSeconds;
    }

private:

    timeval timeValue;
    time_t timeValueSeconds;
    tm* values;

};

}

#endif /* TIMESTAMP_HPP */

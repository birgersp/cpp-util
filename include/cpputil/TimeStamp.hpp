/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include <map>
#include <sys/time.h>
#include <cpputil/core.hpp>

#include "DayOfWeek.hpp"

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

class Timestamp
{
public:

	static DayOfWeek integerToDayOfWeek(int integer)
	{
		switch (integer)
		{
		case 0: return DayOfWeek::SUNDAY;
		case 1: return DayOfWeek::MONDAY;
		case 2: return DayOfWeek::TUESDAY;
		case 3: return DayOfWeek::WEDNESDAY;
		case 4: return DayOfWeek::THURSDAY;
		case 5: return DayOfWeek::FRIDAY;
		case 6: return DayOfWeek::SATURDAY;
		}
	}

	Timestamp(ulong secondsSinceEpoch) :
	secondsSinceEpoch(secondsSinceEpoch)
	{
		time_t secondsSinceEpochInt = (time_t) secondsSinceEpoch;
		tm* values = localtime(&secondsSinceEpochInt);
		year = values->tm_year + 1900;
		month = values->tm_mon + 1;
		dayOfMonth = values->tm_mday;
		dayOfWeek = integerToDayOfWeek(values->tm_wday);
		hour = values->tm_hour;
		minute = values->tm_min;
		second = values->tm_sec;
	}

	Timestamp() :
	Timestamp(getCurrentSecondsSinceEpoch())
	{
	}

	uint getDayOfMonth() const
	{
		return dayOfMonth;
	}

	DayOfWeek getDayOfWeek() const
	{
		return dayOfWeek;
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

	StringRef getDayOfWeekName() const
	{
		auto iterator = dayOfWeekNames.find(dayOfWeek);
		return iterator->second;
	}

	uint getDayOfWeekIndex() const
	{
		auto iterator = dayOfWeekIndices.find(dayOfWeek);
		return iterator->second;
	}

private:

	ulong secondsSinceEpoch;
	uint year, month, dayOfMonth, hour, minute, second;
	DayOfWeek dayOfWeek;

};

}

#endif /* TIMESTAMP_HPP */

/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include "Day_of_week.hpp"
#include <map>
#include <sys/time.h>

inline ulong get_current_seconds_since_epoch()
{
	timeval time_value;
	gettimeofday(&time_value, 0);
	time_t time_value_seconds = time_value.tv_sec;
	ulong seconds_since_epoch = (ulong) time_value_seconds;
	return seconds_since_epoch;
}

class Timestamp
{
public:

	static Day_of_week integer_to_day_of_week(int integer)
	{
		switch (integer)
		{
		case 0: return Day_of_week::SUNDAY;
		case 1: return Day_of_week::MONDAY;
		case 2: return Day_of_week::TUESDAY;
		case 3: return Day_of_week::WEDNESDAY;
		case 4: return Day_of_week::THURSDAY;
		case 5: return Day_of_week::FRIDAY;
		case 6: return Day_of_week::SATURDAY;
		}
	}

	Timestamp(ulong seconds_since_epoch) :
	seconds_since_epoch(seconds_since_epoch)
	{
		time_t seconds_since_epoch_int = (time_t) seconds_since_epoch;
		tm* values = localtime(&seconds_since_epoch_int);
		year = values->tm_year + 1900;
		month = values->tm_mon + 1;
		day_of_month = values->tm_mday;
		day_of_week = integer_to_day_of_week(values->tm_wday);
		hour = values->tm_hour;
		minute = values->tm_min;
		second = values->tm_sec;
	}

	Timestamp() :
	Timestamp(get_current_seconds_since_epoch())
	{
	}

	uint get_day_of_month() const
	{
		return day_of_month;
	}

	Day_of_week get_day_of_week() const
	{
		return day_of_week;
	}

	uint get_hour() const
	{
		return hour;
	}

	uint get_minute() const
	{
		return minute;
	}

	uint get_month() const
	{
		return month;
	}

	uint get_second() const
	{
		return second;
	}

	ulong get_seconds_since_epoch() const
	{
		return seconds_since_epoch;
	}

	uint get_year() const
	{
		return year;
	}

	String_ref get_day_of_week_name() const
	{
		auto iterator = day_of_week_names.find(day_of_week);
		return iterator->second;
	}

	uint get_day_of_week_index() const
	{
		auto iterator = day_of_week_indices.find(day_of_week);
		return iterator->second;
	}

private:

	ulong seconds_since_epoch;
	uint year, month, day_of_month, hour, minute, second;
	Day_of_week day_of_week;

};

#endif /* TIMESTAMP_HPP */

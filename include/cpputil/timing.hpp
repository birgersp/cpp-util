/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef TIMING_HPP
#define TIMING_HPP

#include <sys/time.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

class Timer
{
public:

	static unsigned long current_time_mS()
	{
		struct timeval current_time_value;
		gettimeofday(&current_time_value, 0);
		return current_time_value.tv_sec * 1000 + current_time_value.tv_usec / 1000;
	}

	Timer()
	{
		restart();
	}

	unsigned long elapsed_mS() const
	{
		unsigned long current_time = current_time_mS();
		return (current_time - prev_time);
	}

	void restart()
	{
		prev_time = current_time_mS();
	}

private:

	unsigned long prev_time;

};

inline void sleep_mS(int milliseconds)
{
#if defined(_WIN32) || defined(__CYGWIN__)
	Sleep(milliseconds);
#elif defined(__linux__)
	usleep(milliseconds * 1000);
#endif
}

#endif /* TIMING_HPP */

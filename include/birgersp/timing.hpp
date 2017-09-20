#ifndef TIMING_HPP
#define TIMING_HPP

#include <sys/time.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

namespace birgersp
{

class Timer
{
public:

    Timer()
    {
        restart();
    }

    elapsedMS()
    {
        long currentTime = currentTimeMS();
        return (currentTime - prevTime);
    }

    restart()
    {
        prevTime = currentTimeMS();
    }

private:

    struct timeval currentTimeValue;
    long prevTime;

    currentTimeMS()
    {
        gettimeofday(&currentTimeValue, 0);
        return currentTimeValue.tv_sec * 1000 + currentTimeValue.tv_usec / 1000;
    }

};

static void sleepMS(int milliseconds)
{
#if defined(_WIN32) || defined(__CYGWIN__)
    Sleep(milliseconds);
#elif defined(__linux__)
    usleep(milliseconds / 1000);
#endif
}

}

#endif /* TIMING_HPP */

#ifndef TIMING_HPP
#define TIMING_HPP

#include <sys/time.h>

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

}

#endif /* TIMING_HPP */

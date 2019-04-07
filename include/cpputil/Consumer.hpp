#ifndef CONSUMER_HPP
#define CONSUMER_HPP

namespace cpputil
{

template<class T>
class Consumer
{
public:

    virtual void consume(const T& arg) = 0;

};

}

#endif /* CONSUMER_HPP */


#ifndef CONSUMER_HPP
#define CONSUMER_HPP

namespace birgersp
{

template<class T>
class Consumer
{
public:

    virtual void accept(T arg) = 0;

};

}

#endif /* CONSUMER_HPP */


#ifndef PROVIDER_HPP
#define PROVIDER_HPP

#include "Consumer.hpp"
#include <vector>

namespace cpputil
{

template<class T>
class Provider
{
public:

    void addConsumer(Consumer<T>& consumer)
    {
        consumers.push_back(&consumer);
    }

    void notifyAll(T arg)
    {
        for (Consumer<T>* observer : consumers)
            observer->accept(arg);
    }

private:

    std::vector<Consumer<T>*> consumers;

};

}

#endif /* PROVIDER_HPP */


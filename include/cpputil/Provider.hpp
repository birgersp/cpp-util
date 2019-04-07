#ifndef PROVIDER_HPP
#define PROVIDER_HPP

#include "Consumer.hpp"
#include "Source.hpp"
#include <vector>

namespace cpputil
{

template<class T>
class Provider : public Source<T>
{
public:

    void addConsumer(Consumer<T>& consumer) override
    {
        consumers.push_back(&consumer);
    }

    void notifyAll(const T& arg)
    {
        for (Consumer<T>* observer : consumers)
            observer->accept(arg);
    }

private:

    std::vector<Consumer<T>*> consumers;

};

}

#endif /* PROVIDER_HPP */


/**
 * @author birgersp
 * https://github.com/birgersp
 */

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

	void invokeConsumers(const T& arg)
	{
		for (Consumer<T>* consumer : consumers)
			consumer->consume(arg);
	}

	void operator()(const T& arg)
	{
		invokeConsumers(arg);
	}

private:

	std::vector<Consumer<T>*> consumers;

};

}

#endif /* PROVIDER_HPP */


/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include "core.hpp"
#include "Consumer.hpp"
#include "Source.hpp"
#include <vector>

template<class T>
class Producer : public Source<T>
{
public:

	void add_consumer(Consumer<T>& consumer) override
	{
		consumers.push_back(&consumer);
	}

	void invoke_consumers(const T& arg)
	{
		for (Consumer<T>* consumer : consumers)
			consumer->consume(arg);
	}

	void operator()(const T& arg)
	{
		invoke_consumers(arg);
	}

private:

	std::vector<Consumer<T>*> consumers;

};

#endif /* PRODUCER_HPP */


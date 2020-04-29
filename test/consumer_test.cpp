/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "consumer_test.h"

#include <cpputil/Consumer.hpp>
#include <cpputil/Producer.hpp>
#include <cpputil/testing.hpp>

namespace cpputil
{
namespace tests
{

using namespace cpputil;

namespace observing
{

class Dummy_event
{
public:

	int dummy_data = 0;

};

class Dummy_consumer : public Consumer<Dummy_event>
{
public:

	void consume(const Dummy_event& arg) override
	{
		got_event = true;
		last_event = arg;

	};

	bool got_event{false};
	Dummy_event last_event;

};

class Dummy_provider : public Producer<Dummy_event>
{
};

}

void test_consumer_provider()
{
	using namespace observing;

	Dummy_consumer consumer;
	assert_equals(false, consumer.got_event);

	assert_equals(0, consumer.last_event.dummy_data);

	Dummy_provider producer;
	producer.add_consumer(consumer);
	assert_equals(false, consumer.got_event);
	assert_equals(0, consumer.last_event.dummy_data);

	Dummy_event event;
	event.dummy_data = 10;
	producer.invoke_consumers(event);
	assert_equals(true, consumer.got_event);
	assert_equals(10, consumer.last_event.dummy_data);
}

bool test_consumer()
{
	return test(test_consumer_provider);
}

}
}

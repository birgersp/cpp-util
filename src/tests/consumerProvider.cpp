#include "tests.h"

#include <cpputil/Consumer.hpp>
#include <cpputil/Provider.hpp>
#include <cpputil/testing.hpp>

namespace tests
{

using namespace cpputil;

namespace observing
{

class DummyEvent
{
public:

    int dummyData = 0;

};

class DummyConsumer : public Consumer<DummyEvent>
{
public:

    void accept(DummyEvent arg) override
    {
        gotEvent = true;
        lastEvent = arg;

    };

    bool gotEvent{false};
    DummyEvent lastEvent;

};

class DummyProvider : public Provider<DummyEvent>
{
};

}

void testConsumerProvider()
{
    using namespace observing;

    DummyConsumer consumer;
    assertEquals(false, consumer.gotEvent);

    assertEquals(0, consumer.lastEvent.dummyData);

    DummyProvider observable;
    observable.addConsumer(consumer);
    assertEquals(false, consumer.gotEvent);
    assertEquals(0, consumer.lastEvent.dummyData);

    DummyEvent event;
    event.dummyData = 10;
    observable.notifyAll(event);
    assertEquals(true, consumer.gotEvent);
    assertEquals(10, consumer.lastEvent.dummyData);
}

}

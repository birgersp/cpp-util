#include "observing.h"

#include <birgersp/observing.hpp>
#include <birgersp/testing.hpp>

using namespace birgersp;

namespace observing
{

class DummyEvent
{
public:

    int dummyData = 0;

};

class DummyObserver : public Observer<DummyEvent>
{
public:

    virtual void notify(DummyEvent arg)
    {
        gotEvent = true;
        lastEvent = arg;
    }

    bool gotEvent = false;
    DummyEvent lastEvent;

};

class DummyObservable : public Observable<DummyEvent>
{
};

}

void testObserving()
{
    using namespace observing;

    DummyObserver observer;
    assertEquals(false, observer.gotEvent);

    assertEquals(0, observer.lastEvent.dummyData);

    DummyObservable observable;
    observable.addObserver(observer);
    assertEquals(false, observer.gotEvent);
    assertEquals(0, observer.lastEvent.dummyData);

    DummyEvent event;
    event.dummyData = 10;
    observable.notifyAll(event);
    assertEquals(true, observer.gotEvent);
    assertEquals(10, observer.lastEvent.dummyData);
}

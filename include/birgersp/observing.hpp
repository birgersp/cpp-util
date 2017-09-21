#ifndef OBSERVING_HPP
#define OBSERVING_HPP

#include <vector>

namespace birgersp
{

template<class T>
class Observer
{
public:

    virtual void notify(T arg) = 0;

};

template<class T>
class Observable
{
public:

    void addObserver(Observer<T>& observer)
    {
        observers.push_back(&observer);
    }

    void notifyAll(T arg)
    {
        for (Observer<T>* observer : observers)
            observer->notify(arg);
    }

private:

    std::vector<Observer<T>*> observers;

};

}

#endif /* OBSERVING_HPP */

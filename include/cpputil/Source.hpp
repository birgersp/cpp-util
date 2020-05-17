/**
 * @author birgersp
 * https://github.com/birgersp
 */

#pragma once

#include <vector>

template<class T>
class Source
{
public:

	virtual void add_consumer(Consumer<T>& consumer) = 0;

};


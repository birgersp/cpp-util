/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <vector>

template<class T>
class Source
{
public:

	virtual void add_consumer(Consumer<T>& consumer) = 0;

};

#endif /* SOURCE_HPP */


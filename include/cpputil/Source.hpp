/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "Consumer.hpp"
#include <vector>

namespace cpputil
{

template<class T>
class Source
{
public:

	virtual void addConsumer(Consumer<T>& consumer) = 0;

};

}

#endif /* SOURCE_HPP */


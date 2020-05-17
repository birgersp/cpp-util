/**
 * @author birgersp
 * https://github.com/birgersp
 */

#pragma once

template<class T>
class Consumer
{
public:

	virtual void consume(const T& arg) = 0;

	void operator()(const T& arg)
	{
		consume(arg);
	}

};

#ifndef STRING_READER_HPP
#define STRING_READER_HPP

#include "core.hpp"

namespace cpputil
{

class String_reader
{
public:

	struct Result
	{
		String string;
		char leading_character;
	};

	String_reader(String_ref string)
	{
	}

	bool at_end() const
	{
		return false;
	}

	Result read_until(const Vector<char>&)
	{
		Result result;
		return result;
	}
};

}

#endif /* STRING_READER_HPP */


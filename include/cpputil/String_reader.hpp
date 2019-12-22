/**
 * @author birgersp
 * https://github.com/birgersp
 */

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

	String_reader(String string) :
	string(string)
	{
	}

	bool at_end() const
	{
		return index >= string.length();
	}

	Result read_until(const Vector<char>& characters)
	{
		buffer.clear();
		Result result;
		bool done = false;
		while (not (done or at_end()))
		{
			char current_character = string[index];
			for (char character : characters)
			{
				if (character == current_character)
				{
					done = true;
					result.leading_character = character;
					break;
				}
			}
			if (not done)
			{
				buffer += current_character;
			}
			index++;
		}
		result.string = buffer;
		return result;
	}

private:

	String string, buffer;
	uint index = 0;

};

}

#endif /* STRING_READER_HPP */


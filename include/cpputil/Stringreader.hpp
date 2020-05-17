/**
 * @author birgersp
 * https://github.com/birgersp
 */

#pragma once

#include "core.hpp"

class Stringreader
{
public:

	struct Result
	{
		String string;
		char leading_character;
	};

	Stringreader(String string) :
	string(string)
	{
		index = 0;
	}

	bool at_end() const
	{
		return index >= string.length();
	}

	Result read_until(const std::vector<char>& characters)
	{
		buffer.clear();
		Result result;
		bool done = false;
		while (not done)
		{
			if (at_end())
			{
				result.leading_character = '\0';
				done = true;
			}
			else
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
		}
		result.string = buffer;
		return result;
	}

	Result read_rest()
	{
		return read_until({});
	}

private:

	String string, buffer;
	uint index;

};


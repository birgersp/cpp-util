/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef STRING_INTERPRETER_HPP
#define STRING_INTERPRETER_HPP

#include "core.hpp"

class String_interpreter
{
public:

	static bool character_is_empty(char character)
	{
		return character == ' ' || character == '\t';
	}

	String_interpreter(String_ref subject_line, uint& subject_line_character_index) :
	subject_line(subject_line), subject_line_character_index(subject_line_character_index)
	{
	}

	char get_subject_character() const
	{
		return subject_line[subject_line_character_index];
	}

	bool offset_char_is_number(int offset) const
	{
		char offset_char;
		if (get_offset(offset, offset_char))
			if (isdigit(offset_char))
				return true;
		return false;
	}

	bool get_offset(int offset, char& character) const
	{
		int index = subject_line_character_index + offset;
		if (index_is_out_of_bounds(index))
			return false;
		character = subject_line[index];
		return true;
	}

	bool match_offset(int offset, char character) const
	{
		char offset_character;
		if (get_offset(offset, offset_character))
			if (offset_character == character)
				return true;
		return false;
	}

	bool offset_is_out_of_bounds(int offset) const
	{
		int index = subject_line_character_index + offset;
		return index_is_out_of_bounds(index);
	}

	bool index_is_out_of_bounds(int index) const
	{
		if (index < 0 || index >= subject_line.size())
			return true;
		else
			return false;
	}

private:

	String_ref subject_line;
	uint& subject_line_character_index;

};

#endif /* STRING_INTERPRETER_HPP */

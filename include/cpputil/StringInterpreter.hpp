#ifndef STRINGINTERPRETER_HPP
#define STRINGINTERPRETER_HPP

#include "core.hpp"

namespace cpputil
{

class StringInterpreter
{
public:

	static bool characterIsEmpty(char character)
	{
		return character == ' ' || character == '\t';
	}

	StringInterpreter(StringRef subjectLine, uint& subjectLineCharacterIndex) :
	subjectLine(subjectLine), subjectLineCharacterIndex(subjectLineCharacterIndex)
	{
	}

	char getSubjectCharacter() const
	{
		return subjectLine[subjectLineCharacterIndex];
	}

	bool offsetCharIsNumber(int offset) const
	{
		char offsetChar;
		if (getOffset(offset, offsetChar))
			if (isdigit(offsetChar))
				return true;
		return false;
	}

	bool getOffset(int offset, char& character) const
	{
		int index = subjectLineCharacterIndex + offset;
		if (indexIsOutOfBounds(index))
			return false;
		character = subjectLine[index];
		return true;
	}

	bool matchOffset(int offset, char character) const
	{
		char offsetCharacter;
		if (getOffset(offset, offsetCharacter))
			if (offsetCharacter == character)
				return true;
		return false;
	}

	bool offsetIsOutOfBounds(int offset) const
	{
		int index = subjectLineCharacterIndex + offset;
		return indexIsOutOfBounds(index);
	}

	bool indexIsOutOfBounds(int index) const
	{
		if (index < 0 || index >= subjectLine.size())
			return true;
		else
			return false;
	}

private:

	StringRef subjectLine;
	uint& subjectLineCharacterIndex;

};

}

#endif /* STRINGINTERPRETER_HPP */

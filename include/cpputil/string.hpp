/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef STRING_HPP
#define STRING_HPP

#include <cpputil/core.hpp>

#include <vector>
#include <string>

namespace cpputil
{

inline std::vector<std::string> split_string(String_ref string, char delimiter)
{
	std::vector<std::string> result;

	if (string != "")
	{
		int i1 = 0, i2;
		i2 = string.find(delimiter);
		while (i2 != -1)
		{
			result.push_back(string.substr(i1, i2 - i1));
			i1 = i2 + 1;
			i2 = string.find(delimiter, i1);
		}
		result.push_back(string.substr(i1));
	}

	return result;
}

inline void to_lower_case(Mutable_string_ref string)
{
	std::locale locale;
	for (uint i = 0; i < string.length(); i++)
		string[i] = std::tolower(string[i], locale);
}

namespace stringcompare
{

struct String_difference
{
	uint line;
	std::string string1Line, string2Line;
};

inline bool find_string_difference(String_ref string1, String_ref string2, String_difference& difference)
{
	std::vector<std::string> string1Lines = split_string(string1, '\n');
	std::vector<std::string> string2Lines = split_string(string2, '\n');

	if (string1Lines.size() > string2Lines.size())
	{
		difference.line = string2Lines.size() + 1;
		difference.string1Line = string1Lines[string2Lines.size()];
		difference.string2Line = "";
		return true;
	}

	if (string2Lines.size() > string1Lines.size())
	{
		difference.line = string1Lines.size() + 1;
		difference.string1Line = "";
		difference.string2Line = string2Lines[string1Lines.size()];
		return true;
	}

	uint no_of_lines = string1Lines.size();

	uint line_index = 0;
	while (line_index < no_of_lines)
	{
		String_ref string1Line = string1Lines[line_index];
		String_ref string2Line = string2Lines[line_index];
		if (string1Line != string2Line)
		{
			difference.line = line_index + 1;
			difference.string1Line = string1Line;
			difference.string2Line = string2Line;
			return true;
		}
		line_index++;
	}
	return false;
}

}

}

#endif /* STRING_HPP */

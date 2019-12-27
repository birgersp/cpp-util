/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef STRING_HPP
#define STRING_HPP

#include "core.hpp"
#include <vector>
#include <string>

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
	for (uint i = 0; i < string.length(); i++)
		string[i] = std::tolower(string[i]);
}

namespace stringcompare
{

struct String_difference
{
	uint line;
	std::string string1_line, string2_line;
};

inline bool find_string_difference(String_ref string1, String_ref string2, String_difference& difference)
{
	std::vector<std::string> string1_lines = split_string(string1, '\n');
	std::vector<std::string> string2_lines = split_string(string2, '\n');

	if (string1_lines.size() > string2_lines.size())
	{
		difference.line = string2_lines.size() + 1;
		difference.string1_line = string1_lines[string2_lines.size()];
		difference.string2_line = "";
		return true;
	}

	if (string2_lines.size() > string1_lines.size())
	{
		difference.line = string1_lines.size() + 1;
		difference.string1_line = "";
		difference.string2_line = string2_lines[string1_lines.size()];
		return true;
	}

	uint no_of_lines = string1_lines.size();

	uint line_index = 0;
	while (line_index < no_of_lines)
	{
		String_ref string1_line = string1_lines[line_index];
		String_ref string2_line = string2_lines[line_index];
		if (string1_line != string2_line)
		{
			difference.line = line_index + 1;
			difference.string1_line = string1_line;
			difference.string2_line = string2_line;
			return true;
		}
		line_index++;
	}
	return false;
}

}

#endif /* STRING_HPP */

/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>

#include "core.hpp"

inline bool read_file(String_ref filename, Mutable_string_ref data)
{
	std::ifstream infile(filename);

	data.clear();

	if (infile.is_open())
	{
		std::string line;
		if (std::getline(infile, line))
		{
			data += line;
			while (std::getline(infile, line))
				data += "\n" + line;
		}
		return true;
	}

	return false;
}

inline Vector<String> read_file_lines(String_ref filename)
{
	std::ifstream infile(filename);
	Vector<String> lines;
	if (infile.is_open())
	{
		std::string line;
		while (std::getline(infile, line))
			lines.push_back(line);
	}
	else
	{
		throw function_exception("Could not open file.");
	}
	return lines;
}

inline void write_file(String_ref filename, String_ref data)
{
	std::ofstream file;
	file.open(filename, std::ios::out);
	if (file.is_open() == false)
		throw function_exception("Failed to open file");
	file << data;
	file.close();
}

#endif /* FILE_HPP */

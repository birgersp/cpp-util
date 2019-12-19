/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>

namespace cpputil
{

bool readFile(StringRef filename, MutableStringRef data)
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

}

#endif /* FILE_HPP */


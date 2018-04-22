#ifndef STRING_HPP
#define STRING_HPP

#include <cpputil/core.hpp>

#include <vector>
#include <string>

namespace cpputil
{

std::vector<std::string> splitString(StringRef string, char delimiter)
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

void toLowerCase(std::string& string)
{
    std::locale locale;
    for (uint i = 0; i < string.length(); i++)
        string[i] = std::tolower(string[i], locale);
}

}

#endif /* STRING_HPP */

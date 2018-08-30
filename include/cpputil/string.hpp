#ifndef STRING_HPP
#define STRING_HPP

#include <cpputil/core.hpp>

#include <vector>
#include <string>

namespace cpputil
{

inline std::vector<std::string> splitString(StringRef string, char delimiter)
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

inline void toLowerCase(MutableStringRef string)
{
    std::locale locale;
    for (uint i = 0; i < string.length(); i++)
        string[i] = std::tolower(string[i], locale);
}

namespace stringcompare
{

struct StringDifference
{
    uint line;
    std::string string1Line, string2Line;
};

inline bool findStringDifference(StringRef string1, StringRef string2, StringDifference& difference)
{
    std::vector<std::string> string1Lines = splitString(string1, '\n');
    std::vector<std::string> string2Lines = splitString(string2, '\n');

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

    uint noOfLines = string1Lines.size();

    uint lineIndex = 0;
    while (lineIndex < noOfLines)
    {
        StringRef string1Line = string1Lines[lineIndex];
        StringRef string2Line = string2Lines[lineIndex];
        if (string1Line != string2Line)
        {
            difference.line = lineIndex + 1;
            difference.string1Line = string1Line;
            difference.string2Line = string2Line;
            return true;
        }
        lineIndex++;
    }
    return false;
}

}

}

#endif /* STRING_HPP */

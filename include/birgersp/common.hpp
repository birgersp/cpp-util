#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>

#define toString(val) std::to_string(val)

namespace birgersp
{

std::string getFunctionName(const std::string& functionHeader)
{
    int i0 = functionHeader.find(" ");
    int i1 = functionHeader.find("(");
    return functionHeader.substr(i0 + 1, i1 - i0 - 1);
}

}

#endif /* COMMON_HPP */


#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <vector>

namespace birgersp
{

static std::string getFunctionName(const std::string& functionHeader)
{
    int i0 = functionHeader.find(" ");
    int i1 = functionHeader.find("(");
    return functionHeader.substr(i0 + 1, i1 - i0 - 1);
}

}

#define toString(value) std::to_string(value)

#endif /* COMMON_HPP */


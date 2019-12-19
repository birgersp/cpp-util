/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef COMMON_HPP
#define COMMON_HPP

#include <cpputil/core.hpp>

#include <string>
#include <vector>

namespace cpputil
{

inline std::string getFunctionName(StringRef functionHeader)
{
	int i0 = functionHeader.find(" ");
	int i1 = functionHeader.find("(");
	return functionHeader.substr(i0 + 1, i1 - i0 - 1);
}

}

#endif /* COMMON_HPP */

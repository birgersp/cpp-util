/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef CORE_HPP
#define CORE_HPP

#include <string>
#include <vector>

#if defined(_WIN32) || defined(__CYGWIN__)
#define OS_WINDOWS
#endif

using uint = unsigned int;

#ifdef OS_WINDOWS
using ulong = unsigned long;
#endif

using String = std::string;
using c_string = const char*;
using String_ref = const std::string&;
using Mutable_string_ref = std::string&;

template <typename T>
using Vector = std::vector<T>;

#endif /* CORE_HPP */

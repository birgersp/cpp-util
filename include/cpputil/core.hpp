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

typedef unsigned int uint;

#ifdef OS_WINDOWS
typedef unsigned long ulong;
#endif

typedef std::string String;
typedef const char* c_string;
typedef const std::string& String_ref;
typedef std::string& Mutable_string_ref;

template <typename T>
using Vector = std::vector<T>;

#endif /* CORE_HPP */

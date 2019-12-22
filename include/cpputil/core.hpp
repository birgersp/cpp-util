/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef CORE_HPP
#define CORE_HPP

#include <string>

#if defined(_WIN32) || defined(__CYGWIN__)
#define OS_WINDOWS
#endif

typedef unsigned int uint;

#ifdef OS_WINDOWS
typedef unsigned long ulong;
#endif

typedef const char* c_string;
typedef const std::string& String_ref;
typedef std::string& Mutable_string_ref;

#endif /* CORE_HPP */

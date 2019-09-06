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

typedef const char* cString;
typedef const std::string& StringRef;
typedef std::string& MutableStringRef;

#endif /* CORE_HPP */

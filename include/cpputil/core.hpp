/**
 * @author birgersp
 * https://github.com/birgersp
 */

#pragma once

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
using String_ref = const String&;
using Mutable_string_ref = String&;

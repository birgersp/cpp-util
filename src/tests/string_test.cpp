#include "tests.h"

#include <cpputil/testing.hpp>
#include <cpputil/stringifying.hpp>

namespace cpputil
{
namespace tests
{

void testSplitString()
{
    registerTest();
    std::string subject =
            "first line\n"
            "second line\n"
            "third line\n"
            ""
            ;
    std::vector<std::string> result = splitString(subject, '\n');

    assertEquals(4, result.size());
    assertEquals("first line", result[0]);
    assertEquals("second line", result[1]);
    assertEquals("third line", result[2]);
    assertEquals("", result[3]);
}

void testSplitEmptyString()
{
    registerTest();
    std::vector<std::string> result = splitString("", '\n');
    assertEquals(0, result.size());
}

void testToLowerCase()
{
    registerTest();
    std::string subject = "Hello World!";
    toLowerCase(subject);
    assertEquals("hello world!", subject);
}

bool testStringUtils()
{
    std::vector<BoolFunction> tests = {
        testSplitString,
        testSplitEmptyString,
        testToLowerCase
    };

    return testAll(tests);
}

}
}

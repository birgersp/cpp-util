#include <iostream>

#include <vector>
#include <cpputil/testing.hpp>

#include "demoTests.h"

#include "consumer_test.h"
#include "string_test.h"
#include "stringifying_test.h"
#include "timing_test.h"

int main(int argc, char** argv)
{
    using namespace cpputil;

    printLine("Demo testing");
    demo::demoTests();

    printLine("Performing actual tests");
    std::vector<cpputil::BoolFunction> testFunctions = {
        tests::testConsumer,
        tests::testStringUtils,
        tests::testStringifying,
        tests::testTiming
    };

    if (cpputil::allSucceed(testFunctions))
    {
        printLine("All (real) tests succeeded");
        return 0;
    }

    return 1;
}

#include <iostream>

#include <vector>
#include <cpputil/testing.hpp>

#include "demoTests.h"

#include "core_test.h"
#include "consumer_test.h"
#include "string_test.h"
#include "stringifying_test.h"
#include "timing_test.h"
#include "map_test.h"

int main(int argc, char** argv)
{
	using namespace cpputil;

	printLine("Demo testing");
	demo::demoTests();

	printLine("Performing actual tests");
	std::vector<cpputil::BoolFunction> testFunctions = {
		tests::testCore,
		tests::testConsumer,
		tests::testStringUtils,
		tests::testStringifying,
		tests::testTiming,
		tests::testMap
	};

	if (cpputil::allSucceed(testFunctions))
	{
		printLine("All (real) tests succeeded");
		return 0;
	}

	return 1;
}

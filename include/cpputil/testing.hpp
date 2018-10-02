#ifndef TESTING_HPP
#define TESTING_HPP

#include <cpputil/core.hpp>
#include <cpputil/common.hpp>
#include <cpputil/printing.hpp>
#include <cpputil/errorhandling.hpp>
#include <cpputil/string.hpp>

#include <vector>
#include <string>

namespace cpputil
{

typedef void (*TestFunction) (void);
typedef bool (*BoolFunction) (void);

namespace testing
{

class TestFailed : public Exception
{
public:

    TestFailed(const SourceOrigin& origin, StringRef info) :
    Exception(origin, info)
    {
    }
};

class ComparisonTestFailed : public TestFailed
{
public:

    ComparisonTestFailed(const SourceOrigin& origin, StringRef expected, StringRef actual) :
    TestFailed(origin, generateReason(expected, actual))
    {
    }

    ComparisonTestFailed(const SourceOrigin& origin, StringRef expected, StringRef actual, const stringcompare::StringDifference& difference) :
    TestFailed(origin, generateReason(expected, actual, difference))
    {
    }

private:

    static std::string generateReason(StringRef expected, StringRef actual)
    {
        return "Assertion failed\n\tExpected: " + expected + "\tActual: " + actual;
    }

    static std::string generateReason(StringRef expected, StringRef actual, const stringcompare::StringDifference& difference)
    {
        bool anyNewlines = ((expected.find("\n") != -1) || (actual.find("\n") != -1));
        std::string message;
        if (anyNewlines)
        {
            message = "Assertion failed\n\tExpected:\n" + expected + "\n\tActual:\n" + actual;
            message += "\n\t(Line " + std::to_string(difference.line) + ") " + difference.string1Line + " | " + difference.string2Line;
        }
        else
            message = "Assertion failed\n\tExpected: " + expected + "\tActual: " + actual;
        return message;
    }
};

class Tester
{
public:

    Tester()
    {
        clearLastTest();
    }

    void registerTest(SourceOrigin sourceOrigin)
    {
        setLastTestOrigin(sourceOrigin);
        lastTestState = TestState::NO_ASSERTIONS;
    }

    void makeAssertion(bool expression, SourceOrigin sourceOrigin)
    {
        setLastTestOrigin(sourceOrigin);
        if (!expression)
            throw TestFailed(lastTestOrigin, "Assertion failed");
    }

    void makeEqualsAssertion(float expected, float actual, float delta, SourceOrigin sourceOrigin)
    {
        setLastTestOrigin(sourceOrigin);
        float min = actual - delta;
        float max = actual + delta;
        if (expected < min || expected > max)
            throw ComparisonTestFailed(lastTestOrigin, std::to_string(expected), std::to_string(actual));
    }

    void makeEqualsAssertion(float expected, float actual, SourceOrigin sourceOrigin)
    {
        makeEqualsAssertion(expected, actual, 0, sourceOrigin);
    }

    void makeEqualsAssertion(int expected, int actual, SourceOrigin sourceOrigin)
    {
        setLastTestOrigin(sourceOrigin);
        if (expected != actual)
            throw ComparisonTestFailed(lastTestOrigin, std::to_string(expected), std::to_string(actual));
    }

    void makeEqualsAssertion(unsigned int expected, unsigned int actual, SourceOrigin sourceOrigin)
    {
        setLastTestOrigin(sourceOrigin);
        if (expected != actual)
            throw ComparisonTestFailed(lastTestOrigin, std::to_string(expected), std::to_string(actual));
    }

    void makeEqualsAssertion(StringRef expected, StringRef actual, SourceOrigin sourceOrigin)
    {
        setLastTestOrigin(sourceOrigin);
        stringcompare::StringDifference difference;
        if (stringcompare::findStringDifference(expected, actual, difference))
            throw ComparisonTestFailed(lastTestOrigin, "\"" + expected + "\"", "\"" + actual + "\"", difference);
    }

    void makeEqualsAssertion(const char* expected, const char* actual, SourceOrigin sourceOrigin)
    {
        makeEqualsAssertion(std::string(expected), std::string(actual), sourceOrigin);
    }

    void makeEqualsAssertion(bool expected, bool actual, SourceOrigin sourceOrigin)
    {
        setLastTestOrigin(sourceOrigin);
        if (expected != actual)
            throw ComparisonTestFailed(lastTestOrigin, boolToString(expected), boolToString(actual));
    }

    void makeEqualsAssertion(char expected, char actual, SourceOrigin sourceOrigin)
    {
        setLastTestOrigin(sourceOrigin);
        if (expected != actual)
            throw ComparisonTestFailed(lastTestOrigin, std::string(1, expected), std::string(1, actual));
    }

    void performTest(TestFunction function)
    {
        try
        {
            clearLastTest();
            function();
            if (lastTestState == TestState::NOT_PASSED)
                lastTestState = TestState::PASSED;
        }
        catch (TestFailed e)
        {
            lastTestOrigin = e.getOrigin();
            lastTestMessage = e.getReason();
        }
        catch (Exception e)
        {
            lastTestMessage = e.toString();
            if (lastTestState != TestState::DISABLED)
                lastTestState = TestState::NOT_PASSED;
        }
    }

    bool test(TestFunction function)
    {
        performTest(function);

        bool passed;

        std::string statusString, headerString;

        if (lastTestState == TestState::NO_ASSERTIONS)
        {
            statusString = "INVALID";
            passed = false;
        }
        else if (lastTestState == TestState::PASSED)
        {
            statusString = "OK";
            passed = true;
        }
        else if (lastTestState == TestState::NOT_PASSED)
        {
            statusString = "FAILED";
            passed = false;
        }
        else if (lastTestState == TestState::DISABLED)
        {
            statusString = "IGNORED";
            passed = true;
        }

        if (hasTestOrigin)
            headerString = lastTestOrigin.functionHeader;
        else
            headerString = "(UNKNOWN TEST - NO ASSERTIONS)";

        std::string outputString;
        outputString += statusString;
        outputString += "\t";
        outputString += headerString;

        if (!passed && hasTestOrigin)
            outputString += "\n" + getSourceOriginLinkMessage(lastTestOrigin, "error", "Test failed");

        if (lastTestMessage.size() > 0)
            outputString += "\n\tReason: " + lastTestMessage;

        printLine(outputString);
        return passed;
    }

    bool testAll(const std::vector<TestFunction>& functions)
    {
        bool allTestsSucceeded = true;
        for (TestFunction function : functions)
        {
            if (!test(function))
                allTestsSucceeded = false;
        }
        return allTestsSucceeded;
    }

    void disableTest(SourceOrigin sourceOrigin)
    {
        setLastTestOrigin(sourceOrigin);
        lastTestState = TestState::DISABLED;
        throw Exception(lastTestOrigin, "Test disabled");
    }

private:

    enum class TestState
    {
        PASSED,
        NOT_PASSED,
        DISABLED,
        NO_ASSERTIONS
    } lastTestState;

    SourceOrigin lastTestOrigin;
    std::string lastTestMessage;
    bool hasTestOrigin;

    std::string boolToString(bool value)
    {
        return value ? "true" : "false";
    }

    void clearLastTest()
    {
        lastTestMessage = "";
        lastTestState = TestState::NO_ASSERTIONS;
        hasTestOrigin = false;
    }

    void setLastTestOrigin(SourceOrigin origin)
    {
        lastTestOrigin = origin;
        lastTestMessage = "";
        lastTestState = TestState::NOT_PASSED;
        hasTestOrigin = true;
    }
};

static Tester _tester;

inline Tester& getTester()
{
    return _tester;
}

}

inline bool test(TestFunction function)
{
    printLine("Performing 1 test");
    bool result = testing::getTester().test(function);
    printLine("");
    return result;
}

inline bool testAll(std::vector<TestFunction>& functions)
{
    if (functions.size() == 1)
        return test(functions[0]);
    else
    {
        printLine("Performing " + std::to_string(functions.size()) + " tests");
        bool result = testing::getTester().testAll(functions);
        printLine("");
        return result;
    }
}

inline bool allSucceed(const std::vector<BoolFunction>& boolFunctions)
{
    bool success = true;
    for (auto function : boolFunctions)
        if (!function())
            success = false;
    return success;
}

}

#define cppUtilGetSourceOrigin() cpputil::SourceOrigin(__PRETTY_FUNCTION__, __FILE__, __LINE__)
#define registerTest() cpputil::testing::getTester().registerTest(cppUtilGetSourceOrigin())
#define assertTrue(expression) cpputil::testing::getTester().makeAssertion(expression, cppUtilGetSourceOrigin())
#define assertApproxEqual(expected, actual, delta) cpputil::testing::getTester().makeEqualsAssertion(expected, actual, delta, cppUtilGetSourceOrigin())
#define assertEquals(expected, actual) cpputil::testing::getTester().makeEqualsAssertion(expected, actual, cppUtilGetSourceOrigin())
#define disableTest() cpputil::testing::getTester().disableTest(cppUtilGetSourceOrigin())

#endif /* TESTING_HPP */

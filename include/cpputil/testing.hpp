#ifndef TESTING_HPP
#define TESTING_HPP

#include <cpputil/common.hpp>
#include <cpputil/printing.hpp>
#include <cpputil/errorhandling.hpp>

#include <vector>
#include <string>

namespace cpputil
{

typedef void (*TestFunction) (void);
typedef bool (*BoolFunction) (void);

namespace testing
{

class AssertionFailedException : public Exception
{
public:

    AssertionFailedException(const SourceOrigin origin, const std::string& expected, const std::string& actual) :
    Exception(origin, "Expected: \"" + expected + "\"\tActual: \"" + actual + "\"")
    {
    }

private:

    const std::string message;

};

class Tester
{
public:

    Tester()
    {
        clearLastTest();
    }

    void registerTest(const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestOrigin(SourceOrigin(functionHeader, fileName, lineNumber));
        lastTestState = TestState::NO_ASSERTIONS;
    }

    void makeAssertion(bool expression, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        makeEqualsAssertion(true, expression, functionHeader, fileName, lineNumber);
    }

    void makeEqualsAssertion(float expected, float actual, float delta, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestOrigin(SourceOrigin(functionHeader, fileName, lineNumber));
        float min = actual - delta;
        float max = actual + delta;
        if (expected < min || expected > max)
            throw AssertionFailedException(lastTestOrigin, std::to_string(expected), std::to_string(actual));
    }

    void makeEqualsAssertion(float expected, float actual, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        makeEqualsAssertion(expected, actual, 0, functionHeader, fileName, lineNumber);
    }

    void makeEqualsAssertion(int expected, int actual, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestOrigin(SourceOrigin(functionHeader, fileName, lineNumber));
        if (expected != actual)
            throw AssertionFailedException(lastTestOrigin, std::to_string(expected), std::to_string(actual));
    }

    void makeEqualsAssertion(std::string expected, std::string actual, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestOrigin(SourceOrigin(functionHeader, fileName, lineNumber));
        if (expected != actual)
            throw AssertionFailedException(lastTestOrigin, expected, actual);
    }

    void makeEqualsAssertion(bool expected, bool actual, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestOrigin(SourceOrigin(functionHeader, fileName, lineNumber));
        if (expected != actual)
            throw AssertionFailedException(lastTestOrigin, boolToString(expected), boolToString(actual));
    }

    void makeEqualsAssertion(char expected, char actual, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestOrigin(SourceOrigin(functionHeader, fileName, lineNumber));
        if (expected != actual)
            throw AssertionFailedException(lastTestOrigin, std::string(1, expected), std::string(1, actual));
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
        catch (AssertionFailedException e)
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
            outputString += "\n\t" + lastTestOrigin.fileName + ":" + std::to_string(lastTestOrigin.lineNumber) + ": error: Test failed";

        if (lastTestMessage.size() > 0)
            outputString += "\n\t" + lastTestMessage;

        printString(outputString);
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

    void disableTest(const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestOrigin(SourceOrigin(functionHeader, fileName, lineNumber));
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
    printString("Performing 1 test");
    bool result = testing::getTester().test(function);
    printString("");
    return result;
}

inline bool testAll(std::vector<TestFunction>& functions)
{
    if (functions.size() == 1)
        return test(functions[0]);
    else
    {
        printString("Performing " + std::to_string(functions.size()) + " tests");
        bool result = testing::getTester().testAll(functions);
        printString("");
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

#define registerTest() cpputil::testing::getTester().registerTest(__PRETTY_FUNCTION__, __FILE__, __LINE__)
#define assertTrue(expression) cpputil::testing::getTester().makeAssertion(expression, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define assertApproxEqual(expected, actual, delta) cpputil::testing::getTester().makeEqualsAssertion(expected, actual, delta, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define assertEquals(expected, actual) cpputil::testing::getTester().makeEqualsAssertion(expected, actual, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define disableTest() cpputil::testing::getTester().disableTest(__PRETTY_FUNCTION__, __FILE__, __LINE__)

#endif /* TESTING_HPP */

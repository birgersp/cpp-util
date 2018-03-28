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

struct Test
{

    Test(bool succeeded, SourceOrigin origin, std::string message) :
    succeeded(succeeded), origin(origin), message(message)
    {
    }

    bool succeeded;
    SourceOrigin origin;
    std::string message;

};

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

    void registerTest(const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestOrigin(SourceOrigin(functionHeader, fileName, lineNumber));
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

    Test makeTest(TestFunction function)
    {
        bool testSucceeded = false;
        std::string testMessage;
        try
        {
            hasNewTestOrigin = false;
            function();
            testSucceeded = true;
        }
        catch (AssertionFailedException e)
        {
            lastTestOrigin = e.getOrigin();
            testMessage = e.getReason();
        }
        catch (Exception e)
        {
            testMessage = e.toString();
        }
        Test result(
                    testSucceeded,
                    lastTestOrigin,
                    testMessage
                    );
        return result;
    }

    bool test(TestFunction function)
    {
        const Test test = makeTest(function);

        std::string line;
        if (hasNewTestOrigin)
        {
            if (test.succeeded)
                line += "OK";
            else
            {
                line += "FAILED";
            }
            line += "\t" + test.origin.functionHeader;
            if (!test.succeeded)
                line += "\n\t" + test.origin.fileName + ":" + std::to_string(test.origin.lineNumber) + ": error: Test failed";
        }
        else
            line = "INVALID\t(UNKNOWN TEST)";

        if (test.message.length() > 0)
            line += "\n\t" + test.message;

        printString(line);
        return test.succeeded;
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
        throw Exception(lastTestOrigin, "Test disabled");
    }

private:

    SourceOrigin lastTestOrigin;
    bool hasNewTestOrigin = false;

    std::string boolToString(bool value)
    {
        return value ? "true" : "false";
    }

    void setLastTestOrigin(SourceOrigin origin)
    {
        lastTestOrigin = origin;
        hasNewTestOrigin = true;
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

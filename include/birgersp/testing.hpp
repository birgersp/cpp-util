#ifndef TESTING_HPP
#define TESTING_HPP

#include <birgersp/common.hpp>
#include <birgersp/printing.hpp>

#include <vector>
#include <string>

namespace birgersp
{

typedef void (*TestFunction) (void);

namespace testing
{

class Test
{
public:

    Test(const bool succeeded, const std::string functionName, const std::string fileName, const int lineNumber, const std::string message) :
    succeeded(succeeded), functionName(functionName), fileName(fileName), lineNumber(lineNumber), message(message)
    {
    }

    const bool succeeded;
    const std::string functionName;
    const std::string fileName;
    const int lineNumber;
    const std::string message;
};

class AssertionFailedException
{
public:

    AssertionFailedException(const std::string& message) :
    message(message)
    {
    }

    AssertionFailedException(const std::string& expected, const std::string& actual) :
    message("Expected: \"" + expected + "\"\tActual: \"" + actual + "\"")
    {
    }

    const std::string& getMessage()
    {
        return message;
    }

private:

    const std::string message;
};

class Tester
{
public:

    void makeAssertion(bool expression, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestedFunction(functionHeader, fileName, lineNumber);
        if (!expression)
            throw AssertionFailedException("Boolean expression is false");
    }

    void makeEqualsAssertion(float expected, float actual, float delta, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestedFunction(functionHeader, fileName, lineNumber);
        float min = actual - delta;
        float max = actual + delta;
        if (expected < min || expected > max)
            throw AssertionFailedException(std::to_string(expected), std::to_string(actual));
    }

    void makeEqualsAssertion(float expected, float actual, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        makeEqualsAssertion(expected, actual, 0, functionHeader, fileName, lineNumber);
    }

    void makeEqualsAssertion(std::string expected, std::string actual, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        if (expected != actual)
            throw AssertionFailedException(expected, actual);
    }

    Test makeTest(TestFunction function)
    {
        bool testSucceeded = true;
        std::string testMessage;
        try
        {
            lastTestedFunction.reset();
            function();
        }
        catch (AssertionFailedException e)
        {
            testSucceeded = false;
            testMessage = e.getMessage();
        }
        Test result(
                    testSucceeded,
                    getFunctionName(lastTestedFunction.functionHeader),
                    lastTestedFunction.fileName,
                    lastTestedFunction.lineNumber,
                    testMessage
                    );
        return result;
    }

    bool test(TestFunction function)
    {
        Test test = makeTest(function);

        std::string line;
        if (test.functionName.length() > 0)
        {
            if (test.succeeded)
                line += "OK";
            else
            {
                line += "FAILED";
            }
            line += "\t" + test.functionName;
            if (!test.succeeded)
                line += ", file \"" + test.fileName + "\"" + ": line " + std::to_string(test.lineNumber) + ": " + test.message;
        }
        else
            line = "INVALID";

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

private:

    struct
    {
        std::string functionHeader;
        std::string fileName;
        int lineNumber;

        void reset()
        {
            functionHeader = "";
            fileName = "";
            lineNumber = 0;
        };
    } lastTestedFunction;

    void setLastTestedFunction(const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        lastTestedFunction.functionHeader = functionHeader;
        lastTestedFunction.fileName = fileName;
        lastTestedFunction.lineNumber = lineNumber;
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

}

#define assertTrue(expression) birgersp::testing::getTester().makeAssertion(expression, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define assertApproxEqual(expected, actual, delta) birgersp::testing::getTester().makeEqualsAssertion(expected, actual, delta, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define assertEquals(expected, actual) birgersp::testing::getTester().makeEqualsAssertion(expected, actual, __PRETTY_FUNCTION__, __FILE__, __LINE__)

#endif /* TESTING_HPP */

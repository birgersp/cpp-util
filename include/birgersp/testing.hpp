#ifndef TESTING_HPP
#define TESTING_HPP

#include "common.hpp"
#include "printing.hpp"

#include <vector>
#include <string>

namespace birgersp
{

struct Test
{

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

    AssertionFailedException(const std::string message) :
    message(message)
    {
    }

    const std::string& getMessage()
    {
        return message;
    }

private:

    const std::string message;
};

typedef void (*TestFunction) (void);

class Tester
{
public:

    void makeAssertion(bool expression, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestedFunction(functionHeader, fileName, lineNumber);
        if (!expression)
            throw AssertionFailedException("Boolean expression is false");
    }

    void makeEqualsAssertion(float expected, float actual, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestedFunction(functionHeader, fileName, lineNumber);
        if (expected != actual)
            throw AssertionFailedException("Expected: \"" + toString(expected) + "\"\tActual: \"" + toString(actual) + "\"");
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
                line += ", file \"" + test.fileName + "\"" + ": line " + toString(test.lineNumber) + ": " + test.message;
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

    void setLastTestedFunction(const std::string& functionHeader, std::string fileName, int lineNumber)
    {
        lastTestedFunction.functionHeader = functionHeader;
        lastTestedFunction.fileName = fileName;
        lastTestedFunction.lineNumber = lineNumber;
    }
};

static Tester _tester;

static bool test(TestFunction function)
{
    return _tester.test(function);
}

static bool testAll(std::vector<TestFunction>& functions)
{
    return _tester.testAll(functions);
}

}

#define assertTrue(expression) birgersp::_tester.makeAssertion(expression, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define assertEquals(expected, actual) birgersp::_tester.makeEqualsAssertion(expected, actual, __PRETTY_FUNCTION__, __FILE__, __LINE__)

#endif /* TESTING_HPP */

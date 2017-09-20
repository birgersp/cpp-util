#ifndef TESTING_HPP
#define TESTING_HPP

#include "common.hpp"
#include "logging.hpp"

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

    std::vector<Test> makeTests(std::vector<TestFunction>& functions)
    {
        std::vector<Test> tests;
        for (auto function : functions)
        {
            bool testSucceeded = true;
            std::string testMessage;
            try
            {
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
            tests.push_back(result);
        }
        return tests;
    }

    bool testAll(std::vector<TestFunction>& functions)
    {
        bool allTestsSucceeded = true;
        std::vector<Test> tests = makeTests(functions);
        for (auto test : tests)
        {
            std::string line;
            if (test.succeeded)
                line += "OK";
            else
            {
                line += "FAILED";
                allTestsSucceeded = false;
            }
            line += ":\t";
            line += test.functionName + ", file \"" + test.fileName + "\": line " + toString(test.lineNumber);

            if (!test.succeeded)
                line += ": " + test.message;

            logString(line);
        }
        return allTestsSucceeded;
    }

private:

    struct
    {
        std::string functionHeader;
        std::string fileName;
        int lineNumber;
    } lastTestedFunction;

    void setLastTestedFunction(const std::string& functionHeader, std::string fileName, int lineNumber)
    {
        lastTestedFunction.functionHeader = functionHeader;
        lastTestedFunction.fileName = fileName;
        lastTestedFunction.lineNumber = lineNumber;
    }
};

Tester _tester;

bool testAll(std::vector<TestFunction>& functions)
{
    return _tester.testAll(functions);
}

}

#define assertTrue(expression) birgersp::_tester.makeAssertion(expression, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define assertEquals(expected, actual) birgersp::_tester.makeEqualsAssertion(expected, actual, __PRETTY_FUNCTION__, __FILE__, __LINE__)

#endif /* TESTING_HPP */

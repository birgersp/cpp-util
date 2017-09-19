#ifndef TESTING_HPP
#define TESTING_HPP

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#define assertTrue(value) makeAssertion(value, getFunctionName(__PRETTY_FUNCTION__), __FILE__, __LINE__)
#define assertEquals(expected, actual) makeEqualsAssertion(expected, actual, getFunctionName(__PRETTY_FUNCTION__), __FILE__, __LINE__)

namespace birgersp
{

namespace testing
{

std::string prevTestFunctionName;
std::string prevTestFileName;
int prevTestLineNumber;
std::string prevTestMessage;

typedef std::exception AssertionFailedException;
typedef void (*Test) (void);

bool performTests(std::vector<Test>& tests)
{
    bool anyTestFailed = false;
    for (auto test : tests)
    {
        prevTestMessage = "";
        bool currentTestFailed;
        try
        {
            test();
            currentTestFailed = false;
        }
        catch (AssertionFailedException e)
        {
            currentTestFailed = true;
            anyTestFailed = true;
        }

        std::string testInfo = prevTestFunctionName + "\t(" + prevTestFileName + ":" + std::to_string(prevTestLineNumber) + ")";
        if (currentTestFailed)
            testInfo = "FAILED:\t" + testInfo + "\t" + prevTestMessage;
        else
            testInfo = "OK:\t" + testInfo;

        logger::log(testInfo);
    }

    return !anyTestFailed;
}

void makeAssertion(bool value, std::string functionName, std::string fileName, int lineNumber)
{
    prevTestFunctionName = functionName;
    prevTestFileName = fileName;
    prevTestLineNumber = lineNumber;

    if (!value)
        throw AssertionFailedException();
}

void makeEqualsAssertion(float expected, float actual, std::string functionName, std::string fileName, int lineNumber)
{
    bool result = expected == actual;
    if (!result)
        prevTestMessage = "Expected: " + std::to_string(expected) + "\tActual: " + std::to_string(actual);
    makeAssertion(result, functionName, fileName, lineNumber);
}

void makeEqualsAssertion(const std::string& expected, const std::string& actual, std::string functionName, std::string fileName, int lineNumber)
{
    bool result = expected == actual;
    if (!result)
        prevTestMessage = "Expected: \"" + expected + "\"\tActual: \"" + actual + "\"";
    makeAssertion(result, functionName, fileName, lineNumber);
}

}

}

#endif /* TESTING_HPP */


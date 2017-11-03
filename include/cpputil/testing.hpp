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

class AssertionFailedException : public Exception
{
public:

    AssertionFailedException(const std::string& function, const std::string& filename, int line, const std::string& expected, const std::string& actual) :
    Exception(function, filename, line, "Expected: \"" + expected + "\"\tActual: \"" + actual + "\"")
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
        setLastTestedFunction(functionHeader, fileName, lineNumber);
    }

    void makeAssertion(bool expression, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestedFunction(functionHeader, fileName, lineNumber);

        if (!expression)
            throw Exception(functionHeader, fileName, lineNumber, "Boolean expression is false");
    }

    void makeEqualsAssertion(float expected, float actual, float delta, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestedFunction(functionHeader, fileName, lineNumber);

        float min = actual - delta;
        float max = actual + delta;
        if (expected < min || expected > max)
            throw AssertionFailedException(functionHeader, fileName, lineNumber, std::to_string(expected), std::to_string(actual));
    }

    void makeEqualsAssertion(float expected, float actual, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        makeEqualsAssertion(expected, actual, 0, functionHeader, fileName, lineNumber);
    }

    void makeEqualsAssertion(std::string expected, std::string actual, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
        setLastTestedFunction(functionHeader, fileName, lineNumber);
        if (expected != actual)
            throw AssertionFailedException(functionHeader, fileName, lineNumber, expected, actual);
    }

    Test makeTest(TestFunction function)
    {
        bool testSucceeded = false;
        std::string testMessage;
        try
        {
            lastTestedFunction.reset();
            function();
            testSucceeded = true;
        }
        catch (AssertionFailedException e)
        {
            setLastTestedFunction(e.getFunctionName(), e.getFilename(), e.getLine());
            testMessage = e.getReason();
        }
        catch (Exception e)
        {
            testMessage = e.toString();
        }
        Test result(
                    testSucceeded,
                    lastTestedFunction.functionName,
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
                line += ", file \"" + test.fileName + "\"" + ": line " + std::to_string(test.lineNumber);
        }
        else
            line = "INVALID: UNREGISTERED TEST";

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
        setLastTestedFunction(functionHeader, fileName, lineNumber);
        throw Exception(functionHeader, fileName, lineNumber, "Test disabled");
    }

private:

    struct
    {
        std::string functionName;
        std::string fileName;
        int lineNumber;

        void reset()
        {
            functionName = "";
            fileName = "";
            lineNumber = 0;
        };
    } lastTestedFunction;

    void setLastTestedFunction(const std::string& functionName, const std::string& fileName, int lineNumber)
    {
        lastTestedFunction.functionName = functionName;
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

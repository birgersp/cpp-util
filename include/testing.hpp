#ifndef TESTING_HPP
#define TESTING_HPP

#include <vector>
#include <string>

namespace birgersp
{

namespace testing
{

typedef void (*TestFunction) (void);

class Tester
{
public:

    void makeAssertion(bool expression, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
    }

    void makeEqualsAssertion(float expected, float actual, const std::string& functionHeader, const std::string& fileName, int lineNumber)
    {
    }

    void performTests(std::vector<TestFunction>& functions)
    {
        for (auto function : functions)
        {
            // TODO: invoke function, perform test
        }
    }

private:

    bool testFailed;

};

Tester _tester;

}

}

#define assertTrue(expression) birgersp::testing::_tester.makeAssertion(expression, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define assertEquals(expected, actual) birgersp::testing::_tester.makeEqualsAssertion(expected, actual, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define performTests(tests) birgersp::testing::_tester.performTests(tests)

#endif /* TESTING_HPP */


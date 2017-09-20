
#include "birgersp/testing.hpp"

void test1()
{
    assertEquals(3, 2 + 1);
    assertTrue(1 + 1 == 2);
}

void test2()
{
    assertTrue(true);
    assertTrue(false);
}

int main(int argc, char** argv)
{
    std::vector<birgersp::TestFunction> testFunctions = {
        test1,
        test2
    };

    if (birgersp::testAll(testFunctions))
    {
        return 0;
    }
    else
    {
        birgersp::logError("Error: Some tests failed");
        return 1;
    }

    return 0;
}



#include "testing.hpp"

void test1()
{
    assertEquals(3, 1 + 1);
    assertTrue(1 + 1 == 2);
}

void test2()
{
    assertTrue(true);
}

int main(int argc, char** argv)
{
    std::vector<birgersp::testing::TestFunction> testFunctions = {
        test1,
        test2
    };

    performTests(testFunctions);

    return 0;
}


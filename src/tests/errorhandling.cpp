#include "tests.h"

#include <birgersp/printing.hpp>
#include <birgersp/errorhandling.hpp>

namespace tests
{

void throwException()
{
    throw functionException("(ignore me)");
}

void throwConsequentialException()
{
    try
    {
        throwException();
    }
    catch (birgersp::Exception e)
    {
        throw consequentialException(e);
    }
}

void demoErrorHandling()
{
    try
    {
        throwException();
    }
    catch (birgersp::Exception e)
    {
        birgersp::printString(e.toString());
    }

    try
    {
        throwConsequentialException();
    }
    catch (birgersp::Exception e)
    {
        birgersp::printString(e.toString());
    }
}

}

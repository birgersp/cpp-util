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
    catch (cpputil::Exception e)
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
    catch (cpputil::Exception e)
    {
        cpputil::printString(e.toString());
    }

    try
    {
        throwConsequentialException();
    }
    catch (cpputil::Exception e)
    {
        cpputil::printString(e.toString());
    }
}

}

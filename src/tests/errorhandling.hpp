#ifndef TESTERRORHANDLING_HPP
#define TESTERRORHANDLING_HPP

#include <birgersp/errorhandling.hpp>

void throwException()
{
    throw functionException("(demo exception)");
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

#endif /* TESTERRORHANDLING_HPP */

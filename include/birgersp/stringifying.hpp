#ifndef STRINGIFIABLE_HPP
#define STRINGIFIABLE_HPP

#include <string>
#include <typeinfo>

namespace birgersp
{

class Stringifiable
{
public:

    virtual std::string toString()
    {
        std::string string(typeid (*this).name());
        return string;
    }

};

}

#endif /* STRINGIFIABLE_HPP */


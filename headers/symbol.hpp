#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <iostream>
#include <vector>
#include <string>

namespace april
{
    enum class Type
    {
        STRING,
        UNDEFINED,
        INTEGER,
        DOUBLE
    };

    union Value
    { 
        std::string* _sval;  
        long long _ival;
        double _dval;
    };

    struct Symbol
    {
        std::string name;
        Type type;
        Value value;
        bool is_constant;
    };
}

#endif //SYMBOL_HPP
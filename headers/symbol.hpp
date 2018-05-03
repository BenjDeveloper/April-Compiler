#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <iostream>
#include <vector>

namespace april
{
    enum class Type
    {
        UNDEFINED,
        INTEGER,
        DOUBLE
    };

    union Value
    {
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
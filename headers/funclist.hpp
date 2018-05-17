#ifndef FUNC_LIST_HPP
#define FUNC_LIST_HPP

#include <map>
#include "symbol.hpp"
#include "node.hpp"

namespace april
{
    class Symbol;

    namespace list
    {
        Symbol* size(Symbol*);
        Symbol* append(Symbol*, Symbol*);
        Symbol* index(Symbol*, Symbol*);
        Symbol* remove(Symbol*, Symbol*);
    }

    namespace string
    {
        Symbol* size(Symbol*);
        bool isNumber(Symbol*);
    }

    namespace cast
    {
        Symbol* toDouble(Symbol*);
        Symbol* toInt(Symbol*);
        Symbol* toString(Symbol*);
    }

    namespace io
    {
        void println(Symbol*);
        void _print();
        void print(Symbol*);
        Symbol* input();
    }
}

#endif //FUNC_LIST_HPP
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
    }
}

#endif //FUNC_LIST_HPP
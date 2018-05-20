#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <iostream>
#include <vector>

#include "expression.hpp"
#include "statement.hpp"

namespace april
{
    enum class BlockScope
    {
        FOR,
        FUNCTION,
        IF,
        UNDEFINED
    };

    class Block: public Expression
    {
        public:
            std::vector<Statement*> statements;
            std::vector<Symbol*> locals;
            Block* prev;
            bool stop;
            BlockScope type_scope;
            std::vector<Symbol*> vars_tmp;

        public:
            Block():prev(nullptr), stop(false), type_scope(BlockScope::UNDEFINED) {}
            ~Block();
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //BLOCK_HPP
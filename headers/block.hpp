#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <iostream>
#include <vector>

#include "expression.hpp"
#include "statement.hpp"

namespace april
{
    class Block: public Expression
    {
        public:
            std::vector<Statement*> statements;
            std::vector<Symbol*> locals;
            Block* prev;

        public:
            Block():prev(nullptr) {}
            ~Block();
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //BLOCK_HPP
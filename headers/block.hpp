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
            bool stop;

        public:
            Block():prev(nullptr), stop(false) {}
            ~Block();
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //BLOCK_HPP
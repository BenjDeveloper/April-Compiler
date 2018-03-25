#ifndef FORLOOP_HPP
#define FORLOOP_HPP

#include "expression.hpp"
#include "statement.hpp"
#include "block.hpp"

namespace april 
{
    class ForLoop: public Statement 
    {
        private:
            Expression* condition;
            Block*  block;

        public:
            ForLoop(Expression* condition, Block* block): condition(condition), block(block) {}
            ~ForLoop() { delete condition; delete block; }
            virtual llvm::Value* codeGen(CodeGenContext&);
            Type getType() { return Type::expression; } 
    };
}

#endif //FORLOOP_HPP
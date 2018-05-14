#ifndef IF_HPP
#define IF_HPP

#include "statement.hpp"
#include "block.hpp"

namespace april
{
    class If: public Statement
    {
        private:
            Expression* expr;
            Block* _then;
            Block* _else;
        
        public:
            If(Expression* expr, Block* _then):expr(expr), _then(_then), _else(nullptr) {}
            If(Expression* expr, Block* _then, Block* _else):expr(expr), _then(_then), _else(_else) {}
            ~If();
            Symbol* codeGen(CodeGenContext&);
        
    };
}

#endif //IF_HPP
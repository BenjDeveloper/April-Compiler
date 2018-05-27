#ifndef FOR_HPP
#define FOR_HPP

#include "statement.hpp"
#include "block.hpp"

namespace april
{
    class For: public Statement 
    {
        private:
            Expression* expr;
            Block* block;

        public:
            For(Expression* expr, Block* block):expr(expr), block(block){}
            ~For();
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //FOR_HPP
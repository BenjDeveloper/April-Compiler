#ifndef FOR_ITERATION_HPP
#define FOR_ITERATION_HPP

#include "statement.hpp"
#include "expression.hpp"
#include "block.hpp"
#include "identifier.hpp"

namespace april
{
    class ForIteration: public Statement 
    {
        private:
            Identifier* ident;
            Expression* expr;
            Block* block;

        public:
            ForIteration(Identifier* ident, Expression* expr, Block* block): ident(ident), expr(expr), block(block) {}
            virtual ~ForIteration();
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //FOR_ITERATION_HPP
#ifndef EXPR_STATEMENT_HPP
#define EXPR_STATEMENT_HPP

#include "statement.hpp"
#include "expression.hpp"

namespace april
{
    class ExprStatement: public Statement
    {
        private:
            Expression* expr;
        
        public:
            ExprStatement(Expression* expr): expr(expr) {}
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //EXPR_STATEMENT_HPP
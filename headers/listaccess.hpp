#ifndef LIST_ACCESS_HPP
#define LIST_ACCESS_HPP

#include "expression.hpp"
#include "identifier.hpp"

namespace april
{
    class ListAccess: public Expression
    {
        private:
            Identifier* ident;
            Expression* expr_index;
            Expression* expr;

        public:
            ListAccess(Identifier* ident, Expression* expr_index): ident(ident), expr_index(expr_index) {}
            ListAccess(Expression* expr, Expression* expr_index): expr(expr), expr_index(expr_index) {}
            ~ListAccess();
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //LIST_ACCESS_HPP
#ifndef ASSIGNMENT_HPP
#define ASSIGNMENT_HPP

#include "expression.hpp"
#include "identifier.hpp"

namespace april
{
    class Assignment: public Expression 
    {
        private:
            Identifier* ident;
            Expression* expr;

        public:
            Assignment(Identifier* ident, Expression* expr): ident(ident), expr(expr){}
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif // ASSIGNMENT_HPP
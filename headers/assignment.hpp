#ifndef ASSIGMENT_HPP
#define ASSIGMENT_HPP

#include "expression.hpp"
#include "identifier.hpp"

namespace april
{
    class Assignment: public Expression
    {
        private:
            Expression* expr;
            Identifier* ident;

        public:
            Assignment(Identifier* ident, Expression* expr):ident(ident), expr(expr)  {}
            virtual ~Assignment();
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //ASSIGMENT_HPP
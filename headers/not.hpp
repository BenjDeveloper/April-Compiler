#ifndef NOT_HPP
#define NOT_HPP

#include "expression.hpp"

namespace april
{
    class Not: public Expression
    {
        private:
            Expression* expr;

        public:
            Not(Expression* expr): expr(expr) {}
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //NOT_HPP
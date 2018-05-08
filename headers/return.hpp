#ifndef RETURN_HPP
#define RETURN_HPP

#include "expression.hpp"
#include "statement.hpp"

namespace april
{
    class Return: public Statement
    {
        
        Expression* expr;

        public:
            Return(): expr(nullptr) {}
            Return(Expression* expr): expr(expr) {}
            ~Return();
            Symbol* codeGen(CodeGenContext&);
    };
}

#endif //RETURN_HPP
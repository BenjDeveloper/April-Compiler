#ifndef RETURN_HPP
#define RETURN_HPP

#include "statement.hpp"

namespace april
{
    class Return: public Statement
    {
        private:
            Expression* expr;

        public:
            Return(Expression* expr = nullptr):expr(expr) {}
            ~Return() { if (expr != nullptr) { delete expr; } }
            virtual llvm::Value* codeGen(CodeGenContext&);    
            Type getType() { return Type::expression; }
    };
}

#endif //RETURN_HPP
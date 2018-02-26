#ifndef ASSIGBIOPE_HPP
#define ASSIGBIOPE_HPP

#include "expression.hpp"
#include "identifier.hpp"

namespace april
{
    class AssigBioperator: public Expression
    {
        public:
            Identifier* ident;
            int _operator;
            Expression* expr;
        
        public:
            AssigBioperator(Identifier* ident, int _operator, Expression* expr): ident(ident), _operator(_operator), expr(expr) {}
            ~AssigBioperator() { delete ident; delete expr; }
            llvm::Value* codeGen(CodeGenContext&);
            Type getType() { return Type::expression; }
    };
}

#endif //ASSIGBIOPE_HPP
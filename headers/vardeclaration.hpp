#ifndef VAR_DECLARATION_HPP
#define VAR_DECLARATION_HPP

#include "statement.hpp"
#include "identifier.hpp"
#include "expression.hpp"

namespace april
{
    class VarDeclaration: public Statement
    {
        private:
            Identifier* type;
            Identifier* ident;
            Expression* expr;

        public:
            VarDeclaration(Identifier* ident, Identifier* type, Expression* expr):ident(ident), type(type), expr(expr) {}
            VarDeclaration(Identifier* ident, Identifier* type):ident(ident), type(type), expr(nullptr) {}
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //VAR_DECLARATION_HPP
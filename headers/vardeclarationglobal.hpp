#ifndef VAR_DECLARATION_GLOBAL_HPP
#define VAR_DECLARATION_GLOBAL_HPP

#include "statement.hpp"
#include "identifier.hpp"
#include "expression.hpp"

namespace april
{
    class VarDeclarationGlobal: public Statement
    {
        private:
            Identifier* ident;
            Identifier* type;
            Expression* expr;

        public:
            VarDeclarationGlobal(Identifier* ident, Identifier* type, Expression* expr): ident(ident), type(type), expr(expr) {}
            virtual ~VarDeclarationGlobal();
            virtual Symbol* codeGen (CodeGenContext&); 
    };
}

#endif //VAR_DECLARATION_GLOBAL_HPP
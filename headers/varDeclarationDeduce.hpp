#ifndef VAR_DECLARATION_DECUCE_HPP
#define VAR_DECLARATION_DECUCE_HPP

#include "statement.hpp"
#include "identifier.hpp"
#include "expression.hpp"

namespace april
{
    class VarDeclarationDeduce: public Statement
    {
        private:
            Identifier* ident;
            Expression* expr;
        
        public:
            VarDeclarationDeduce(Identifier* ident, Expression* expr): ident(ident), expr(expr) {}
            ~VarDeclarationDeduce();
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //VAR_DECLARATION_DECUCE_HPP
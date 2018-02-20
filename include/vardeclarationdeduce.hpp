#ifndef VARDECLARATIONDEDUCE_HPP
#define VARDECLARATIONDEDUCE_HPP

#include <iostream>
#include "statement.hpp"
#include "identifier.hpp"
#include "expression.hpp"

namespace april
{
    class VariableDeclarationDeduce: public Statement
    {
        public:
            Identifier& id;
            Expression* expr;

        public:
            VariableDeclarationDeduce(Identifier& id, Expression* expr): id(id), expr(expr) { }
            virtual llvm::Value* codeGen(CodeGenContext&);
            Type getType() { return Type::variable; }
            
    };
}


#endif //VARDECLARATIONDEDUCE_HPP
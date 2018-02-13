#ifndef VARDECLARATION_HPP
#define VARDECLARATION_HPP

#include "statement.hpp"
#include "identifier.hpp"
#include "expression.hpp"

namespace april
{
    class VariableDeclaration: public Statement
    {
        private:
            const Identifier& type;
            Identifier& id;
            Expression* assignmentExpr;
        
        public:
            VariableDeclaration(const Identifier& type, Identifier& id): type(type), id(id) { assignmentExpr = nullptr; } 
            VariableDeclaration(const Identifier& type, Identifier& id, Expression* assignmentExpr): type(type), id(id), assignmentExpr(assignmentExpr) {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
            Type getType() { return Type::variable; }
    };
}


#endif //VARDECLARATION_HPP 
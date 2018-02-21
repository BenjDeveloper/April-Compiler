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
            Identifier& type;
            Identifier& id;
            Expression* assignmentExpr;
        
        public:
            VariableDeclaration(Identifier& type, Identifier& id): type(type), id(id) { assignmentExpr = nullptr; } 
            VariableDeclaration(Identifier& type, Identifier& id, Expression* assignmentExpr): type(type), id(id), assignmentExpr(assignmentExpr) {}
            const Identifier& getIdentOfVar() { return id; } 
            const Identifier& getIdentOfVarType() { return type; } 
            std::string getVarName() { return id.getName(); }
            std::string getVarTypeName() { return type.getName(); }
            virtual llvm::Value* codeGen(CodeGenContext& context);
            Type getType() { return Type::variable; }
    };
}


#endif //VARDECLARATION_HPP 
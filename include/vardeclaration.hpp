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
			bool is_ref;
        
        public:
			VariableDeclaration(Identifier& type, Identifier& id, bool is_ref) : type(type), id(id), is_ref(is_ref) { assignmentExpr = nullptr; }
			VariableDeclaration(Identifier& type, Identifier& id): type(type), id(id), is_ref(false) { assignmentExpr = nullptr; }
            VariableDeclaration(Identifier& type, Identifier& id, Expression* assignmentExpr): type(type), id(id), assignmentExpr(assignmentExpr), is_ref(false) {}
            const Identifier& getIdentOfVar() { return id; } 
            const Identifier& getIdentOfVarType() { return type; } 
            std::string getVarName() { return id.getName(); }
            std::string getVarTypeName() { return type.getName(); }
			bool isRef() { return is_ref; }
            virtual llvm::Value* codeGen(CodeGenContext& context);
            Type getType() { return Type::variable; }
    };
}


#endif //VARDECLARATION_HPP 
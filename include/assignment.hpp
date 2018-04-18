#ifndef ASSIGNMENT_HPP
#define ASSIGNMENT_HPP

#include "expression.hpp"
#include "identifier.hpp"

namespace april
{
    class Assignment: public Expression //revisar herencia con statement
    {
        public:
            Identifier& lhs;
            Expression& rhs;
            llvm::Value* rhs_value = nullptr;
        public:
			Assignment(Identifier& lhs, Expression& rhs) :lhs(lhs), rhs(rhs) {}
			Assignment(Identifier* lhs, Expression* rhs):lhs(*lhs), rhs(*rhs) {}
            Assignment(Identifier& lhs, Expression& rhs, llvm::Value* rhs_value):lhs(lhs), rhs(rhs), rhs_value(rhs_value) {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
            Type getType() { return Type::expression; }
    };
}

#endif //ASSIGNMENT_HPP
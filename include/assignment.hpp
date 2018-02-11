#ifndef ASSIGNMENT_HPP
#define ASSIGNMENT_HPP

#include "expression.hpp"
#include "identifier.hpp"

namespace april
{
    class Assignment: public Expression
    {
        public:
            Identifier& lhs;
            Expression& rhs;
        
        public:
            Assignment(Identifier& lhs, Expression& rhs):lhs(lhs), rhs(rhs) {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
    };
}

#endif //ASSIGNMENT_HPP
#ifndef BIOPERATOR_HPP
#define BIOPERATOR_HPP

#include "expression.hpp"

namespace april
{
    class BinaryOperator: public Expression
    {
        private:
            int op;
            Expression& lhs;
            Expression& rhs;

        public:
            BinaryOperator(Expression& lhs, int op, Expression& rhs): lhs(lhs), rhs(rhs), op(op) {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
            Type getType() { return Type::expression; }
    };
}

#endif //BIOPERATOR_HPP
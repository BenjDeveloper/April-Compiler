#ifndef EXPRSTATEMENT_HPP
#define EXPRSTATEMENT_HPP

#include "expression.hpp"
#include "statement.hpp"

namespace april
{
    class ExpressionStatement: public Statement
    {
        private:
            Expression& expression;
        
        public:
            ExpressionStatement(Expression& expression): expression(expression) {}
            llvm::Value* codeGen(CodeGenContext& context);
    };
}

#endif //EXPRSTATEMENT_HPP 
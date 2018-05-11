#ifndef ASSIGNMENT_LIST_HPP
#define ASSIGNMENT_LIST_HPP

#include "expression.hpp"

namespace april
{
    class AssignmentList: public Expression
    {
        private:
            Expression* expr;
            Expression* expr_assig;

        public:
            AssignmentList(Expression* expr, Expression* expr_assig): expr(expr), expr_assig(expr_assig) {}
            virtual ~AssignmentList();
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //ASSIGNMENT_LIST_HPP
#ifndef BINARY_OPE
#define BINARY_OPE

#include "expression.hpp"

namespace april
{
    enum class OPE
    {
        PLUS,
        MIN,
        MUL,
        DIV
    };

    class BinaryOpe: public Expression
    {
        private:
            Expression* left;
            Expression* right;
            OPE ope;

        public:
            BinaryOpe(Expression* left, OPE ope, Expression* right):left(left), ope(ope), right(right) {}
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //BINARY_OPE
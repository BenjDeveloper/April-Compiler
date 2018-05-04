#ifndef BOOLEANCMP
#define BOOLEANCMP

#include "expression.hpp"

namespace april
{
    class BooleanCmp: public Expression
    {
        private:
            Expression* left;
            Expression* right;
            int ope;
        
        public:
            BooleanCmp (Expression* left, int ope, Expression* right):left(left), ope(ope), right(right) {}
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //BOOLEANCMP
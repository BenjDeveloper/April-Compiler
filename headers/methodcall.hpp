#ifndef METHOD_CALL_HPP
#define METHOD_CALL_HPP

#include "identifier.hpp"
#include "expression.hpp"

namespace april
{
    class MethodCall : public Expression
    {
        private:
            Identifier* ident;
            ExpressionList* args;

        public:
            MethodCall(Identifier* ident, ExpressionList* args): ident(ident), args(args){}
            Symbol* codeGen(CodeGenContext&);
    };
}

#endif //METHOD_CALL_HPP
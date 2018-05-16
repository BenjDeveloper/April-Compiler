#ifndef METHOD_HANDLE_CAST_HPP
#define METHOD_HANDLE_CAST_HPP

#include "identifier.hpp"
#include "expression.hpp"

namespace april
{
    class MethodHandleCast: public Expression
    {
        private:
            Identifier* ident_method;
            ExpressionList* args;

        public:
            MethodHandleCast(Identifier* ident_method, ExpressionList* args):ident_method(ident_method), args(args) {}
            virtual ~MethodHandleCast();
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //METHOD_HANDLE_CAST_HPP
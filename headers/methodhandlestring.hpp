#ifndef METHOD_HANDLE_STRING_HPP
#define METHOD_HANDLE_STRING_HPP

#include "identifier.hpp"
#include "expression.hpp"

namespace april
{
    class MethodHandleString: public Expression
    {
        private:
            Symbol* sym_expr;
            Identifier* ident_method;
            ExpressionList* args;

        public:
            MethodHandleString(Symbol* sym_expr, Identifier* ident_method, ExpressionList* args): sym_expr(sym_expr), ident_method(ident_method), args(args) {}
            virtual ~MethodHandleString();
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //METHOD_HANDLE_STRING_HPP
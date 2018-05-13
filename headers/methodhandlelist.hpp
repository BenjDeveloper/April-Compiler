#ifndef METHOD_HANDLE_LIST
#define METHOD_HANDLE_LIST

#include "expression.hpp"
#include "identifier.hpp"

namespace april
{
    class MethodHandleList: public Expression
    {
        private:
            Symbol* sym_expr;
            Identifier* ident_method;
            ExpressionList* args;

        public:
            MethodHandleList(Symbol* sym_expr, Identifier* ident_method, ExpressionList* args): sym_expr(sym_expr), ident_method(ident_method), args(args) {}
            virtual ~MethodHandleList();
            virtual Symbol* codeGen(CodeGenContext&);

    };
}

#endif //METHOD_HANDLE_LIST
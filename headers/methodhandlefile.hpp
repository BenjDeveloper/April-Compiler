#ifndef METHOD_HANDLE_FILE_HPP
#define METHOD_HANDLE_FILE_HPP

#include "expression.hpp"
#include "identifier.hpp"

namespace april
{
    class MethodHandleFile: public Expression
    {
        private:
            Symbol* sym_expr;
            Identifier* ident_method;
            ExpressionList* args;
        
        public:
            MethodHandleFile(Symbol* sym_expr, Identifier* ident_method, ExpressionList* args): sym_expr(sym_expr), ident_method(ident_method), args(args) {}
            virtual ~MethodHandleFile();
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //METHOD_HANDLE_FILE_HPP
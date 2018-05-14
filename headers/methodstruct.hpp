#ifndef METHOD_STRUCT_HPP
#define METHOD_STRUCT_HPP

#include "identifier.hpp"
#include "expression.hpp"

namespace april
{
    class MethodStruct: public Expression
    {
        private:
            Identifier* ident_var;
            Identifier* ident_method;
            ExpressionList* args; // aun no se a manejado ya que no poseemos metodos que lo necesiten
            Expression* expr_var;

        public:
            MethodStruct(Identifier* ident_var,Identifier* ident_method, ExpressionList* args): ident_var(ident_var), ident_method(ident_method), args(args){ expr_var = nullptr; }
            MethodStruct(Expression* expr_var, Identifier* ident_method, ExpressionList* args): expr_var(expr_var), ident_method(ident_method), args(args){ ident_var = nullptr; }
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //METHOD_STRUCT_HPP
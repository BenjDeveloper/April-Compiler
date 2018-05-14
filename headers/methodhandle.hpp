#ifndef METHOD_HANDLE_HPP
#define METHOD_HANDLE_HPP

#include "identifier.hpp"
#include "expression.hpp"

namespace april
{
    class MethodHandle: public Expression
    {
        private:
            Identifier* ident_var;
            Identifier* ident_method;
            ExpressionList* args;
            Type type;
            Symbol* sym_var;
            

        public:
            MethodHandle(Identifier* ident_var, Identifier* ident_method, ExpressionList* args, Type type):ident_var(ident_var), ident_method(ident_method), args(args), type(type){ sym_var=nullptr; }
            MethodHandle(Symbol* sym_var, Identifier* ident_method, ExpressionList* args, Type type):sym_var(sym_var), ident_method(ident_method), args(args), type(type){}

            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //METHOD_HANDLE_HPP
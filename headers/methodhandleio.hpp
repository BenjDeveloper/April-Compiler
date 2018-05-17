#ifndef METHOD_HANDLE_IO_HPP
#define METHOD_HANDLE_IO_HPP

#include "identifier.hpp"
#include "expression.hpp"

namespace april
{
    class MethodHandleIo: public Expression
    {
        private:
            Identifier* ident_method;
            ExpressionList* args;

        public:
            MethodHandleIo(Identifier* ident_method, ExpressionList* args):ident_method(ident_method), args(args) {}
            virtual ~MethodHandleIo();
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //METHOD_HANDLE_IO_HPP
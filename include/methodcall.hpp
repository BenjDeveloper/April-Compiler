#ifndef METHODCALL_HPP
#define METHODCALL_HPP

#include "expression.hpp"
#include "identifier.hpp"

namespace april
{
    using ExpressionList = std::vector<Expression*>;

    class MethodCall: public Expression
    {
        private:
            Identifier* id;
            ExpressionList* arguments;
        public:
            MethodCall(Identifier* id, ExpressionList* arguments): id(id), arguments(arguments) {}
            MethodCall(Identifier* id): id(id) {}
            ~MethodCall();
            virtual llvm::Value* codeGen(CodeGenContext& context);
            Type getType() { return Type::expression; }
    };
}

#endif //METHODCALL_HPP
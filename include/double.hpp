#ifndef DOUBLE_HPP
#define DOUBLE_HPP

#include "expression.hpp"

namespace april
{
    class Double: public Expression
    {
        public:
            double value;
        
        public:
            Double(double value): value(value) {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
            Type getType() { return Type::decimal; }
    };
}

#endif //DOUBLE_HPP
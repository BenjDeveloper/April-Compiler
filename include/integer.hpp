#ifndef INTEGER_HPP
#define INTEGER_HPP

#include "expression.hpp"

namespace april
{
    class Integer: public Expression
    {
        public:
            long long value;
        
        public:
            Integer(long long value): value(value) {}
            virtual llvm::Value* codeGen(CodeGenContext&);
            Type getType() { return Type::integer; }
    };
}

#endif //INTEGER_HPP
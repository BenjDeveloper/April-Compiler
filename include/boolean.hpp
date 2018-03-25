#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP

#include "expression.hpp"
#include "codegencontext.hpp"

namespace april
{
    class Boolean: public Expression
    {
        public:
            std::string str_value;
            int int_value;

        public:
            Boolean(std::string);
            virtual llvm::Value* codeGen(CodeGenContext&);
            Type getType() { return Type::boolean; }
    };
}

#endif //BOOLEAN_HPP
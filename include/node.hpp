#ifndef NODE_HPP
#define NODE_HPP

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

//#include "codegencontext.hpp"

namespace april
{
    enum class Type
    {
        integer,
        boolean,
        string,
        decimal,
        identifier,
        expression,
        variable
    };
    
    class CodeGenContext;
    
    class Node
    {
        public:
            virtual ~Node() {}
            virtual llvm::Value* codeGen(CodeGenContext&) = 0;
            virtual Type getType() = 0;
    };
}


#endif //NODE_HPP 
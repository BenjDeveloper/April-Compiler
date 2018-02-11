#ifndef NODE_HPP
#define NODE_HPP

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

//#include "codegencontext.hpp"

namespace april
{
    class CodeGenContext;
    
    class Node
    {
        public:
            virtual ~Node() {}
            virtual llvm::Value* codeGen(CodeGenContext& context) { return NULL; }
    };
}


#endif //NODE_HPP 
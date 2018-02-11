#ifndef CODEGENBLOCK_HPP
#define CODEGENBLOCK_HPP

//--------------------------
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"

namespace april
{
    class CodeGenBlock
    {
        public:
            llvm::BasicBlock* block;
            llvm::Value* returnValue;
            std::map<std::string, llvm::Value*> locals;
    };
}

#endif //CODEGENBLOCK_HPP 
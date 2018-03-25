#ifndef CODEGENBLOCK_HPP
#define CODEGENBLOCK_HPP

//--------------------------
#include <iostream>
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"

namespace april
{
    class CodeGenBlock
    {
        public:
            llvm::BasicBlock* block;
            std::map<std::string, llvm::AllocaInst*> locals;

        public:
            CodeGenBlock(llvm::BasicBlock* block): block(block) { }
            void setCodeBlock(llvm::BasicBlock* bblock) { block = bblock; }
    };
}
#endif //CODEGENBLOCK_HPP 
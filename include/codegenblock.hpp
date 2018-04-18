#ifndef CODEGENBLOCK_HPP
#define CODEGENBLOCK_HPP

//--------------------------
#include <iostream>
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"

namespace april
{
	using VariableTypeMap = std::map<std::string, std::string>;

    class CodeGenBlock
    {
        public:
            llvm::BasicBlock* block;
            std::map<std::string, llvm::AllocaInst*> locals;
			VariableTypeMap types;

        public:
            CodeGenBlock(llvm::BasicBlock* block): block(block) { }
            void setCodeBlock(llvm::BasicBlock* bblock) { block = bblock; }
			VariableTypeMap& getTypeMap() { return types; }
    };
}
#endif //CODEGENBLOCK_HPP 
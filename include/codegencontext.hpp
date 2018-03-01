#ifndef CODEGENCONTEXT_HPP
#define CODEGENCONTEXT_HPP

#include <stack>
#include <map>
#include <list>
#include <set>
#include <vector>
//--------------------------
#include <iostream>
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/Support/raw_ostream.h"
#include <llvm/Support/ManagedStatic.h>

#include "codegenblock.hpp"
#include "block.hpp"
#include "identifier.hpp"

namespace april
{
    enum class ScopeType
    {
        FunctionDeclaration
    };

    class CodeGenContext
    {
        public:
            std::vector<std::string> namesFunctions;

        private:
            std::stack<llvm::FunctionType*> stackFunctionType;
            std::list<CodeGenBlock*> blocks;
            llvm::Function* mainFunction;
            llvm::Module* module;
            llvm::Function* printfFunction;
            llvm::LLVMContext llvmContext;
            int errors;

        public:
            CodeGenContext();
            void optimize();
            llvm::LLVMContext& getGlobalContext() { return llvmContext; }
            bool generateCode(Block& root);
            llvm::Module* getModule() { return this->module; }
            llvm::GenericValue runCode();
            std::map<std::string, llvm::AllocaInst*>& locals()  { return blocks.front()->locals; }
            llvm::BasicBlock* currentBlock() { return blocks.front()->block; }
            void pushBlock(llvm::BasicBlock* block, llvm::FunctionType* fn);
            void popBlock();
            void setupBuildFn();
            llvm::AllocaInst* searchVariable(std::string);
            void setCurrentBlock(llvm::BasicBlock* block) { blocks.front()->setCodeBlock(block); }
            llvm::Type* typeOf(const Identifier&);
            llvm::Type* typeOf(const std::string);
            void addError() { ++errors; }
            llvm::FunctionType* getCurrentFunctionType() { return stackFunctionType.top(); }
	};
}

#endif //CODEGENCONTEXT_HPP 

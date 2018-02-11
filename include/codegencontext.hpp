#ifndef CODEGENCONTEXT_HPP
#define CODEGENCONTEXT_HPP

#include <stack>
#include <map>
#include <list>
#include <set>

//--------------------------
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

namespace april
{
    class CodeGenContext
    {
        private:
            std::stack<CodeGenBlock*> blocks;
            llvm::Function* mainFunction;
            llvm::Module* module;
            llvm::Function* printfFunction;
            llvm::Function* currentFunction;
            llvm::LLVMContext llvmContext;

    
        public:
            CodeGenContext() 
            { 
                llvm::InitializeNativeTarget();
                llvm::InitializeNativeTargetAsmParser();
                llvm::InitializeNativeTargetAsmPrinter();
                module = new llvm::Module("main", llvmContext); 
            }
            void optimize();
            llvm::LLVMContext& getGlobalContext() { return llvmContext; }
            void generateCode(Block& root);
            llvm::Module* getModule() { return this->module; }
            llvm::GenericValue runCode();
            std::map<std::string, llvm::Value*>& locals()  { return blocks.top()->locals; }
            llvm::BasicBlock* currentBlock() { return blocks.top()->block; }

            void pushBlock(llvm::BasicBlock* block)
            {
                blocks.push(new CodeGenBlock()); 
                blocks.top()->returnValue = NULL;
                blocks.top()->block = block; 
            }

            void popBlock()
            {
                CodeGenBlock* top = blocks.top();
                blocks.pop();
                delete top;
            } 

            void setCurrentReturnValue(llvm::Value* value) { blocks.top()->returnValue = value; }
            llvm::Value* getCurrentReturnValue() { return blocks.top()->returnValue; }

            void setupBuildFn();
    };
}

#endif //CODEGENCONTEXT_HPP 
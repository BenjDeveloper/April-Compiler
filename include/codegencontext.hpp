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
	using ValueNames = std::map<std::string, llvm::AllocaInst*>;

	enum class ScopeType
	{
		Function,
		Block
	};

    class CodeGenContext
    {
        public:
            std::vector<std::string> namesFunctions;
			//std::map<std::string, std::vector<bool>> func_args_refs;
			//std::map<std::string, std::vector<std::map<bool, llvm::AllocaInst*>>> func_args_alloc;
			std::map<std::string, llvm::AllocaInst*> map_struct_type;
	
		private:
            std::stack<llvm::FunctionType*> stackFunctionType;
            std::list<CodeGenBlock*> blocks;
            llvm::Function* mainFunction;
            llvm::Module* module;
            llvm::Function* printfFunction;
            llvm::LLVMContext llvmContext;
            int errors;
			ScopeType scope;

        public:
            CodeGenContext();
            void optimize();
            llvm::LLVMContext& getGlobalContext() { return llvmContext; }
            bool generateCode(Block&);
            llvm::Module* getModule() { return this->module; }
            llvm::GenericValue runCode();
            std::map<std::string, llvm::AllocaInst*>& locals()  { return blocks.front()->locals; }
            llvm::BasicBlock* currentBlock() { return blocks.front()->block; }
            void pushBlock(llvm::BasicBlock*, llvm::FunctionType*, ScopeType);
            void popBlock();
            void setupBuildFn();
            llvm::AllocaInst* searchVariable(std::string);
            void setCurrentBlock(llvm::BasicBlock* block) { blocks.front()->setCodeBlock(block); }
            llvm::Type* typeOf(const Identifier&);
            llvm::Type* typeOf(const std::string);
            void valOperator(llvm::Value*&, llvm::Value*&);
            void addError() { ++errors; }
            llvm::FunctionType* getCurrentFunctionType() { return stackFunctionType.top(); }
			ScopeType getScope() { return scope; }
			void renameVariable(std::string, std::string);
			void setVarType(std::string varType, std::string varName) { blocks.front()->getTypeMap()[varName] = varType; }
			std::string getType(std::string);
			void deleteVariable(std::string);
	};
}

#endif //CODEGENCONTEXT_HPP 

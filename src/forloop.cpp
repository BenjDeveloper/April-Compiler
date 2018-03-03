#include <iostream>
#include "../include/forloop.hpp"
#include "../include/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    llvm::Value* ForLoop::codeGen(CodeGenContext& context)
    {
        llvm::Function* function = context.currentBlock()->getParent();
        llvm::BasicBlock* first_cond = llvm::BasicBlock::Create(context.getGlobalContext(), "first_cond", function);
        llvm::BasicBlock* cond_block = llvm::BasicBlock::Create(context.getGlobalContext(), "cond_block");
        llvm::BasicBlock* loop_block = llvm::BasicBlock::Create(context.getGlobalContext(), "loop_block");
        llvm::BasicBlock* else_block = llvm::BasicBlock::Create(context.getGlobalContext(), "else_block");
        llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(context.getGlobalContext(), "merge_block");
        llvm::BranchInst::Create(first_cond, context.currentBlock());

        context.setCurrentBlock(first_cond);
        llvm::Value* first_value = condition->codeGen(context);
        if (first_value == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: falta implementacion del bloque 'then' en el for\n");
            context.addError();
            return nullptr;
        }
        llvm::BranchInst::Create(loop_block, else_block, first_value, context.currentBlock()); // -AQUI

        std::map<std::string, llvm::AllocaInst*> scope_locals;
		std::map<std::string, llvm::AllocaInst*>::iterator it;
		for (it = context.locals().begin(); it != context.locals().end(); it++) { scope_locals[it->first] = it->second; }

        function->getBasicBlockList().push_back(cond_block);
        context.setCurrentBlock(cond_block);
        
		llvm::Value* cond_value = condition->codeGen(context);
        
		if (cond_value == nullptr) 
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: fallo la evaluacion de la expresion del condicional del for\n");
            context.addError();
            return nullptr;
        }
        llvm::BranchInst::Create(loop_block, merge_block, cond_value, context.currentBlock());
       	context.locals() = scope_locals;
        function->getBasicBlockList().push_back(loop_block);
        context.setCurrentBlock(loop_block);
        
        llvm::Value* loop_value = block->codeGen(context);
        if (loop_value == nullptr) 
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: fallo la evaluacion del bloque del for\n");
            context.addError();
            return nullptr;
        }
        llvm::BranchInst::Create(cond_block, context.currentBlock());

        function->getBasicBlockList().push_back(else_block);
        context.setCurrentBlock(else_block); // el for puede aceptar else, aqui se implementaria dicho bloque

        llvm::BranchInst::Create(merge_block, context.currentBlock());
        function->getBasicBlockList().push_back(merge_block);
        context.setCurrentBlock(merge_block);
        
       	context.locals() = scope_locals;
		
		return merge_block;
    }
}

#include <iostream>
#include "../include/conditional.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
	llvm::Value* Conditional::codeGen(CodeGenContext& context)
	{
		llvm::Value* expr_value = expr->codeGen(context);
		
		llvm::Function* function = context.currentBlock()->getParent();
		llvm::BasicBlock* true_block = llvm::BasicBlock::Create(context.getGlobalContext(), "then", function);
		llvm::BasicBlock* false_block = llvm::BasicBlock::Create(context.getGlobalContext(), "else");
		llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(context.getGlobalContext(), "merge");
		llvm::BranchInst::Create(true_block, false_block , expr_value, context.currentBlock());
		std::map<std::string, llvm::AllocaInst*> scope_locals;
		std::map<std::string, llvm::AllocaInst*>::iterator it = context.locals().begin();
		for (it = context.locals().begin(); it != context.locals().end(); it++) { scope_locals[it->first] = it->second; }
		
		bool need_merge = false;
		context.pushBlock(true_block, nullptr); ///aqui
		context.setCurrentBlock(true_block);
		for (it = scope_locals.begin(); it != scope_locals.end(); it++) { context.locals()[it->first] = it->second; }
		llvm::Value* true_value = then_block.codeGen(context);		

		if (true_value == nullptr)
		{
			printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el bloque 'then' esta vacio\n");
            context.addError();
			context.popBlock(); //aqui
            return nullptr;
		}

		if (context.currentBlock()->getTerminator() == nullptr)
		{
			llvm::BranchInst::Create(merge_block, context.currentBlock());
			need_merge = true;
		}
		
		context.popBlock(); //aqui
		context.pushBlock(true_block, nullptr); ///aqui
		function->getBasicBlockList().push_back(false_block);
		context.setCurrentBlock(false_block);
		for (it = scope_locals.begin(); it != scope_locals.end(); it++) { context.locals()[it->first] = it->second; }
		llvm::Value* false_value = nullptr;
		if (has_else)
		{
			false_value = else_block.codeGen(context);
		}
		
		if (context.currentBlock()->getTerminator() == nullptr)
		{
			llvm::BranchInst::Create(merge_block, context.currentBlock());
			need_merge = true;
		}
		context.popBlock(); //aqui
		if (need_merge)
		{
			function->getBasicBlockList().push_back(merge_block);
			context.setCurrentBlock(merge_block);
		}
		return merge_block;
	}
}

#include <map>
#include "../include/scope.hpp"

namespace april
{
	llvm::Value* Scope::codeGen(CodeGenContext& context)
	{
		std::map<std::string, llvm::AllocaInst*> scope_locals;
		std::map<std::string, llvm::AllocaInst*>::iterator it = context.locals().begin();
		for (it = context.locals().begin(); it != context.locals().end(); it++) { scope_locals[it->first] = it->second; }

		llvm::Function* function = context.currentBlock()->getParent();
		llvm::BasicBlock* bblock = llvm::BasicBlock::Create(context.getGlobalContext(), "scope", function);
		llvm::BranchInst::Create(bblock, context.currentBlock());
		llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(context.getGlobalContext(), "merge");
		context.setCurrentBlock(bblock);

		llvm::Value* block_value = block->codeGen(context);

		if (context.currentBlock()->getTerminator() == nullptr)
		{
			llvm::BranchInst::Create(merge_block, context.currentBlock());
			function->getBasicBlockList().push_back(merge_block);
			context.setCurrentBlock(merge_block);
			context.locals() = scope_locals;
			return merge_block;
		}
		context.locals() = scope_locals;
		
		return nullptr;
	}
}

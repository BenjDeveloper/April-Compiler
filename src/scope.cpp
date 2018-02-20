#include "../include/scope.hpp"

namespace april
{
	llvm::Value* Scope::codeGen(CodeGenContext& context)
	{
		llvm::Function* function = context.currentBlock()->getParent();
		llvm::BasicBlock* bblock = llvm::BasicBlock::Create(context.getGlobalContext(), "scope", function);
		llvm::BranchInst::Create(bblock, context.currentBlock());
		llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(context.getGlobalContext(), "merge");

		context.setCurrentBlock(bblock);
		llvm::Value* block_value = block->codeGen(context);
		
		if (context.currentBlock()->getTerminator() == nullptr)
		{
			llvm::ReturnInst::Create(context.getGlobalContext(), 0, context.currentBlock());

			function->getBasicBlockList().push_back(merge_block);
			context.setCurrentBlock(merge_block);

			return merge_block;
		}
		return nullptr;
	}
}

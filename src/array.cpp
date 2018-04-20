#include "../include/array.hpp"
#include "../include/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
	llvm::Value* Array::codeGen(CodeGenContext& context)
	{
		std::vector<llvm::Value*> valueList;
		std::vector<llvm::Type*> typeList;
		llvm::Type* type_array = nullptr;

		int index = 0;
		for (auto para: *exprs)
		{
			llvm::Value* code = para->codeGen(context);
			if (code == nullptr)
				return nullptr;
		
			valueList.push_back(code);
			typeList.push_back(code->getType());
			index += 1;
		}

		llvm::StructType* _array = llvm::StructType::create(context.getGlobalContext(), llvm::makeArrayRef(typeList), "list");
		auto alloc_array = new llvm::AllocaInst(_array, 0, "alloc_list", context.currentBlock());

		std::vector<llvm::Value*> ptr_indices;
		llvm::ConstantInt* const_int_32_0 = llvm::ConstantInt::get(context.getModule()->getContext(), llvm::APInt(32, 0));

		for (int i = 0; i < valueList.size(); ++i)
		{
			ptr_indices.clear();
			ptr_indices.push_back(const_int_32_0);
			llvm::ConstantInt* const_int32 = llvm::ConstantInt::get(context.getModule()->getContext(), llvm::APInt(32, i));
			ptr_indices.push_back(const_int32);
			llvm::Instruction* ptr = llvm::GetElementPtrInst::Create(alloc_array->getType()->getElementType(), alloc_array, ptr_indices, "", context.currentBlock());
			new llvm::StoreInst(valueList[i], ptr, context.currentBlock());
		}
		return alloc_array;
	}
}
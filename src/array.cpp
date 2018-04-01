#include "../include/array.hpp"
#include "../include/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
	llvm::Value* Array::codeGen(CodeGenContext& context)
	{
		std::vector<llvm::Value*> valueList;
		std::vector<llvm::Type*> typeList;
		int index = 0;
		llvm::Type* type_array = nullptr;

		for (auto para: *exprs)
		{
			llvm::Value* code = para->codeGen(context);
			if (code == nullptr)
			{
				return nullptr;
			}
			valueList.push_back(code);

			if (index > 0 && !code->getType()->isPointerTy() && code->getType() != type_array)
			{
				printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el arreglo no puede tener diferentes tipos de datos.\n");
				context.addError();
				return nullptr;
			}
			else if (index == 0)
			{
				type_array = code->getType();
			}
			typeList.push_back(code->getType());
			index++;
		}

		llvm::StructType* _array = llvm::StructType::create(context.getGlobalContext(), llvm::makeArrayRef(typeList), "_array");
		auto alloc_array = new llvm::AllocaInst(_array, 0, "alloc_array", context.currentBlock());
		
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
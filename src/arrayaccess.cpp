#include "../include/arrayaccess.hpp"
#include "../include/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
	llvm::Value* ArrayAccess::codeGen(CodeGenContext& context)
	{
		llvm::AllocaInst* var = nullptr;
		llvm::Type* var_type = nullptr;
		llvm::Type* var_array_type = nullptr;

		if (expr != nullptr)
		{
			llvm::Value* tmp = expr->codeGen(context);
			var = new llvm::AllocaInst(tmp->getType(), 0, "tmp_access_array_index", context.currentBlock());
			new llvm::StoreInst(tmp, var, context.currentBlock());
			var_type = var->getAllocatedType();
			var_array_type = var->getAllocatedType()->getContainedType(0);
		}
		else
		{
			var = context.searchVariable(id->getName());
			if (var == nullptr)
			{
				printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: variable no inicializada.\n");
				context.addError();
				return nullptr;
			}
			var_type = var->getAllocatedType();
			var_array_type = var_type->getContainedType(0);
		}
		//---------------------------------
		if (var_array_type == nullptr)
		{
			printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: ERROR# 1 ARRAY.\n");
			context.addError();
			return nullptr;
		}
		if (var_array_type->getTypeID() != llvm::StructType::StructTyID)
		{
			printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: ERROR# 2 ARRAY.\n");
			context.addError();
			return nullptr;
		}
		if (var_array_type->getNumContainedTypes() <= index)
		{
			printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: indice fuera del rango del arreglo.\n");
			context.addError();
			return nullptr;
		}

		std::vector<llvm::Value*> ptr_indices;
		llvm::ConstantInt* const_int32_0 = llvm::ConstantInt::get(context.getModule()->getContext(), llvm::APInt(32, 0));
		llvm::ConstantInt* const_int32 = llvm::ConstantInt::get(context.getModule()->getContext(), llvm::APInt(32, index));
		ptr_indices.push_back(const_int32_0);
		ptr_indices.push_back(const_int32);
		auto val = new llvm::LoadInst(var, "load_var", context.currentBlock());
		this->_ptr = llvm::GetElementPtrInst::Create(var_array_type, val, ptr_indices, "get_array_element", context.currentBlock());
		llvm::LoadInst* value = new llvm::LoadInst(this->_ptr, "load_ptr_array", context.currentBlock());
		return value;
	}

}
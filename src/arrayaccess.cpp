#include "../include/arrayaccess.hpp"
#include "../include/codegencontext.hpp"
#include "../include/integer.hpp"
#include "../include/comparasionope.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
	llvm::Value* ArrayAccess::codeGen(CodeGenContext& context)
	{
		llvm::AllocaInst* var = nullptr;
		llvm::Type* var_type = nullptr;
		llvm::Type* var_array_type = nullptr;

		//--------------------------------------

		uint64_t index = _index;
		llvm::ConstantInt* const_int = nullptr;
		llvm::Value* _val_index = nullptr;

		if (expr_index != nullptr)
		{
			_val_index = expr_index->codeGen(context);
			if (!_val_index->getType()->isIntegerTy())
			{
				printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el indice debe ser una expresion de tipo 'int'.\n");
				context.addError();
				return nullptr;
			}

			Integer* int_expr = new Integer(18);
			llvm::Value* int_value = int_expr->codeGen(context);
			
			llvm::CmpInst* cmp = llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_EQ, int_value, _val_index, "cmotmo", context.currentBlock());
			
			if (cmp->getType()->isIntegerTy())
				std::cout << "es integer --> <--" << std::endl;



			

			const_int = llvm::dyn_cast<llvm::ConstantInt>(_val_index);
			if (const_int == nullptr)
				std::cout << "ERROR!!!" << std::endl;

			std::cout << "final" << std::endl;
			if (const_int == nullptr)
			{
				const_int->getValue();
				std::cout << "(1)SHITTTT" << std::endl;
			}
			else
				std::cout << "(1)NO SHITTTT" << std::endl;
		}
		//--------------------------------------


		if (expr != nullptr)
		{
			std::cout << "--> aqui <--" << std::endl;
			llvm::Value* tmp = expr->codeGen(context);
			var = new llvm::AllocaInst(tmp->getType(), 0, "tmp_access_array_index", context.currentBlock());
			new llvm::StoreInst(tmp, var, context.currentBlock());
			var_type = var->getAllocatedType();
			var_array_type = var->getAllocatedType()->getContainedType(0);
		}
		else
		{
			if (context.map_struct_type.find(id->getName()) != context.map_struct_type.end())
				var = context.map_struct_type[id->getName()];
			else
				var = context.searchVariableAll(id->getName());

			if (var == nullptr)
			{
				printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable "+ id->getName()+"  no ha sido inicializada.\n");
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
		llvm::ConstantInt* const_int32 = nullptr;

		if (const_int == nullptr)
		{
			std::cout << "-->> es NULO <<--" << std::endl;
			const_int32 = llvm::ConstantInt::get(context.getModule()->getContext(), llvm::APInt(32, index));
		}
		else
		{
			std::cout << "-->> AQUI <<--" << std::endl;
			const_int32 = llvm::ConstantInt::get(context.getModule()->getContext(), const_int->getValue());
		}
		
		ptr_indices.push_back(const_int32_0);
		ptr_indices.push_back(const_int32);
		
		auto val = new llvm::LoadInst(var, "load_var", context.currentBlock());
		this->_ptr = llvm::GetElementPtrInst::Create(var_array_type, val, ptr_indices, "get_array_element", context.currentBlock());
		llvm::LoadInst* value = new llvm::LoadInst(this->_ptr, "load_ptr_array", context.currentBlock());
		return value;
	}
}
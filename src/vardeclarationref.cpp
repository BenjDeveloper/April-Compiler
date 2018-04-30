#include "../include/vardeclarationref.hpp"
#include "../include/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
	llvm::Value* VarDeclarationRef::codeGen(CodeGenContext& context)
	{
		std::cout << "definicion de una ref!!" << std::endl;
		
		if (context.searchVariableAll(id->getName()))
		{
			printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '" + id->name + "' ya existe\n");
			context.addError();
			return nullptr;
		}

		if (id_obj != nullptr)
		{
			if (!context.searchVariableAll(id_obj->getName()))
			{
				printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '" + id_obj->name + "' NO existe\n");
				context.addError();
				return nullptr;
			}
			llvm::Value* val_obj = id_obj->codeGen(context);
			if (type != nullptr && val_obj->getType() != context.typeOf(type->getName()))
			{
				printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: los tipos de datos son diferentes.\n");
				context.addError();
				return nullptr;
			}
			context.locals()[id->getName()] = context.locals()[id_obj->getName()];
		}
		else
		{
			std::cout << "ref como parametro" << std::endl;
			_expr_ref_type = context.typeOf(type_name);
			//context.locals()[id->getName()] = nullptr;


			//---
			llvm::AllocaInst* alloc = new llvm::AllocaInst(_expr_ref_type, id->getName().c_str(), context.currentBlock());
			context.locals()[id->getName()] = alloc;
		}
		return context.locals()[id->getName()];
	}
}
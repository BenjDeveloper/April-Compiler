#include <iostream>
#include "../include/vardeclaration.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"
#include "../include/array.hpp"

//----------------------------
extern april::STRUCINFO* april_errors;

namespace april
{
    llvm::Value* VariableDeclaration::codeGen(CodeGenContext& context)
    {
		llvm::Type* type_value = nullptr;

        if (context.searchVariable(id.name))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '"+id.name+"' ya existe\n");
            context.addError();
            return nullptr;
        }
        
        type_value = context.typeOf(type.getName());
		
		if (type_value == nullptr)
        {
			printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: tipo no definido");
            context.addError();
            return nullptr;
        }

		//--------------------------------------------------------

		llvm::AllocaInst* alloc = nullptr;

		if (!type_value->isStructTy())
		{
			this->__is_struct = false;
			alloc = new llvm::AllocaInst(type_value, 0, id.name.c_str(), context.currentBlock());
		}
		else
		{
			this->__is_struct = true;
			llvm::Value* array_value = nullptr;
			if (assignmentExpr == nullptr)
			{
				ExpressionList members;
				Array* array = new Array{ &members };
				array_value = array->codeGen(context);
			}
			else
				array_value = assignmentExpr->codeGen(context);
			
			//llvm::Type* _array_type = llvm::PointerType::get(array_value->getType(), 0);

			//alloc = new llvm::AllocaInst(_array_type, id.getName().c_str(), context.currentBlock());
			alloc = new llvm::AllocaInst(array_value->getType(), id.getName().c_str(), context.currentBlock());
			new llvm::StoreInst(array_value, alloc, false, context.currentBlock());

		}
		context.locals()[id.getName()] = alloc;
		context.setVarType(type.getName(), id.getName());

		//--------------------------------------------------------
		if (!type_value->isStructTy() && assignmentExpr != nullptr)
        { 
			llvm::Value* expr_value = assignmentExpr->codeGen(context);
			if (expr_value == nullptr)
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: con el token de tipo "+type.name+"\n");
                context.addError();
                return nullptr;
            }

            //---------------------------------------------
			if (type_value->isDoubleTy() && expr_value->getType()->isIntegerTy())
				expr_value = llvm::CastInst::Create(llvm::CastInst::getCastOpcode(expr_value, true, llvm::Type::getDoubleTy(context.getGlobalContext()), true), expr_value, llvm::Type::getDoubleTy(context.getGlobalContext()), "cast_double", context.currentBlock());
           
			if (type_value->isIntegerTy() && expr_value->getType()->isDoubleTy())
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: al asignar una variable tipo 'int' con un 'double'");
                context.addError();
                return nullptr;
            }
			//---------------------------------------------
			Assignment assn(id, *assignmentExpr, expr_value);
            assn.codeGen(context);
        }
        return alloc;
    }
}

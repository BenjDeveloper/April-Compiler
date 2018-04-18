#include <iostream>
#include "../include/vardeclaration.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"

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
		if (type_value->isStructTy() && context.getScope() != ScopeType::Function)
		{
			alloc = new llvm::AllocaInst(type_value, 0, id.name.c_str(), context.currentBlock());
			context.locals()[id.name] = alloc;
		}
		else
		{
			if (type_value->isStructTy())
				type_value = llvm::PointerType::get(type_value, 0);
			
			alloc = new llvm::AllocaInst(type_value, 0, id.name.c_str(), context.currentBlock());
			context.locals()[id.name] = alloc;

		}
		context.setVarType(type.getName(), id.getName());

		//--------------------------------------------------------

		if (assignmentExpr != nullptr)
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

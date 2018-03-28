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
		llvm::Value* _code = nullptr;
		llvm::AllocaInst* alloc = nullptr;
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

		if (assignmentExpr != nullptr && assignmentExpr->getType() == Type::array)
		{
			_code = assignmentExpr->codeGen(context);
			alloc = new llvm::AllocaInst(_code->getType(), id.name.c_str(), context.currentBlock());
		}
		else
		{
			alloc = new llvm::AllocaInst(type_value, id.name.c_str(), context.currentBlock());
		}
        
		context.locals()[id.name] = alloc;
		

		if (assignmentExpr != nullptr)
        { 
			llvm::Value* expr_value = nullptr;
			if (_code == nullptr)
			{
				expr_value = assignmentExpr->codeGen(context);
			}
			
            if (_code == nullptr && expr_value == nullptr)
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: con el token de tipo "+type.name+"\n");
                context.addError();
                return nullptr;
            }

            //---------------------------------------------
			if (!(assignmentExpr->getType() == Type::array) && type_value->isDoubleTy() && expr_value->getType()->isIntegerTy())
            {
				expr_value = llvm::CastInst::Create(llvm::CastInst::getCastOpcode(expr_value, true, llvm::Type::getDoubleTy(context.getGlobalContext()), true), expr_value, llvm::Type::getDoubleTy(context.getGlobalContext()), "cast_double", context.currentBlock());
            }
           
			if (!(assignmentExpr->getType() == Type::array) && type_value->isIntegerTy() && expr_value->getType()->isDoubleTy())
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: al asignar una variable tipo 'int' con un 'double'");
                context.addError();
                return nullptr;
            }
			//---------------------------------------------
			Assignment assn(id, *assignmentExpr, (_code==nullptr)?(expr_value):(_code));
            assn.codeGen(context);
        }

        return alloc;
    }
}

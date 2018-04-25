#include <iostream>
#include "../include/vardeclaration.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"
#include "../include/errors.hpp"

//----------------------------
// Errors :: [1-10] node -> statemente -> vardeclaration
extern april::STRUCINFO* april_errors;

namespace april
{
    llvm::Value* VariableDeclaration::codeGen(CodeGenContext& context)
    {
		llvm::Type* type_value = nullptr;

        if (context.searchVariable(id.name))
        {
			return Errors::call(context, 1, april_errors->file_name, april_errors->line, id.name);
        }
        
        type_value = context.typeOf(type.getName());
		
		if (type_value == nullptr)
        {
			return Errors::call(context, 2, april_errors->file_name, april_errors->line, "");
        }

		llvm::AllocaInst* alloc = new llvm::AllocaInst(type_value, id.name.c_str(), context.currentBlock());
		context.locals()[id.name] = alloc;

		if (assignmentExpr != nullptr)
        { 
			llvm::Value* expr_value = assignmentExpr->codeGen(context);
			if (expr_value == nullptr)
            {
				return Errors::call(context, 3, april_errors->file_name, april_errors->line, type.name);
            }

            //---------------------------------------------
			if (type_value->isDoubleTy() && expr_value->getType()->isIntegerTy())
            {
				expr_value = llvm::CastInst::Create(llvm::CastInst::getCastOpcode(expr_value, true, llvm::Type::getDoubleTy(context.getGlobalContext()), true), expr_value, llvm::Type::getDoubleTy(context.getGlobalContext()), "cast_double", context.currentBlock());
            }
           
			if (type_value->isIntegerTy() && expr_value->getType()->isDoubleTy())
            {
				return Errors::call(context, 4, april_errors->file_name, april_errors->line, "");
            }
			//---------------------------------------------
			Assignment assn(id, *assignmentExpr, expr_value);
            assn.codeGen(context);
        }

        return alloc;
    }
}

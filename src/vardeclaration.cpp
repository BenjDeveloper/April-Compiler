#include <iostream>
#include "../include/vardeclaration.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"
#include "../include/array.hpp"
#include "../include/arrayaccess.hpp"

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
        
		if (context.map_struct_type.find(type.getName()) != context.map_struct_type.end())
			type_value = context.map_struct_type[type.getName()]->getAllocatedType();
		else
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
			if (type.getName() != "string" && type.getName() != "int" && type.getName() != "double" && type.getName() != "bool")
			{
				std::cout << "num: " << type_value->getContainedType(0)->getNumContainedTypes() << std::endl;
				//-------------------------------------------------------
				if (type.getName() == id.getName())
				{
					printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '" + id.name + "' ya existe.\n");
					context.addError();
					return nullptr;
				}
				
				ExpressionList members;
				//llvm::AllocaInst* var = context.searchVariable(type.getName());
				llvm::AllocaInst* var = context.map_struct_type[type.name];

				auto var_type = var->getAllocatedType();
				auto var_struct_type = var_type->getContainedType(0);
				auto count = var_struct_type->getNumContainedTypes();

				for (decltype(count) i = 0; i < count; ++i)
					members.push_back(new ArrayAccess{ &type, i });

				Array* array = new Array{ &members };
				llvm::Value* array_value = array->codeGen(context);

				alloc = new llvm::AllocaInst(array_value->getType(), id.getName().c_str(), context.currentBlock());
				context.locals()[id.name] = alloc;
				context.map_struct_type[id.name] = alloc;

				new llvm::StoreInst(array_value, context.locals()[id.getName()], false, context.currentBlock());
				return alloc;
				//-------------------------------------------------------
			}
			else
			{
				this->__is_struct = false;
				alloc = new llvm::AllocaInst(type_value, 0, id.name.c_str(), context.currentBlock());
			}
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
			
			alloc = new llvm::AllocaInst(array_value->getType(), id.getName().c_str(), context.currentBlock());
			new llvm::StoreInst(array_value, alloc, false, context.currentBlock());
			context.map_struct_type[id.getName()] = alloc;
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

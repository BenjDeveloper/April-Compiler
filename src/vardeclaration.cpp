#include <iostream>
#include "../include/vardeclaration.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"

//----------------------------

namespace april
{
    llvm::Value* VariableDeclaration::codeGen(CodeGenContext& context)
    {
        if (context.searchVariable(id.name))
        {
            printError("la variable '"+id.name+"' ya existe\n");
            context.addError();
            return nullptr;
        }
        
        // std::cout << "Creating variable declaration " << type.name << ", " << id.name << std::endl;
        llvm::Type* type_value = context.typeOf(type);
        llvm::AllocaInst* alloc = new llvm::AllocaInst(type_value, id.name.c_str(), context.currentBlock());
        context.locals()[id.name] = alloc;
		
        if (assignmentExpr != nullptr)
        { 
            llvm::Value* expr_value = assignmentExpr->codeGen(context);
            if (expr_value == nullptr)
            {
                printError("Error con el token de tipo "+type.name+"\n");
                context.addError();
                return nullptr;
            }
            // condicional para hacer una asignacion de un int a un float se hace un cast al int 
            if (type_value->isDoubleTy() && expr_value->getType()->isIntegerTy())
            {
                auto double_type = llvm::Type::getDoubleTy(context.getGlobalContext());
                auto cast_instr = llvm::CastInst::getCastOpcode(expr_value, true, double_type, true);
                expr_value = llvm::CastInst::Create(cast_instr, expr_value, double_type, "cast", context.currentBlock());
            }
            if (type_value->isIntegerTy() && expr_value->getType()->isDoubleTy())
            {
                printError("Error al asignar una variable tipo int con un float");
                context.addError();
                return nullptr;
            }
            Assignment assn(id, *assignmentExpr, expr_value);
            assn.codeGen(context);
        }

        return alloc;
    }
}

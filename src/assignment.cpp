#include <iostream>
#include "../include/assignment.hpp"
#include "../include/codegencontext.hpp"

//----------------------------
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/Support/raw_ostream.h"
#include <llvm/Support/ManagedStatic.h>

namespace april
{
    llvm::Value* Assignment::codeGen(CodeGenContext& context)
    {
        std::cout << "Creando asignacion para: " << lhs.name << std::endl;
        if (context.locals().find(lhs.name) == context.locals().end())
        {
            std::cerr << "la variable no ha sido declarada: " << lhs.name << std::endl;
            return NULL;
        }



        if (rhs_value != nullptr) { return new llvm::StoreInst(rhs_value, context.locals()[lhs.name], false, context.currentBlock());}
        else 
        { 
            // std::cout << "--->>>" << std::endl;
            // llvm::AllocaInst* v = context.locals()[lhs.name];
            llvm::Value* expr_value = rhs.codeGen(context);
            // std::cout << "--->>>" << std::endl;
           
			// if (v->getType() == llvm::Type::getInt64Ty(context.getGlobalContext()))
			// {
			// 	std::cout << "--> value is Integer fu*king yes!!" << std::endl;
			// }

			// if (v->getType() == llvm::Type::getDoubleTy(context.getGlobalContext()))
			// {
			// 	std::cout << "--> value is un double fu*ing yes!!" << std::endl;
			// }

            // if (expr_value->getType()->isDoubleTy())
            // {
            //     std::cout << "---> expr_value is Double" << std::endl;
            // }

			// if (expr_value->getType()->isIntegerTy())
            // {
            //     std::cout << "---> expr_value is Integer" << std::endl;
            // }

            // if (v->getType()->isIntegerTy() && expr_value->getType()->isDoubleTy())
            // {
            //     std::cerr << "Error al asignar un int con un float: " << lhs.name << std::endl;
            //     exit(1);            
            // }

            return new llvm::StoreInst(expr_value, context.locals()[lhs.name], false, context.currentBlock()); 
        
        }
    }
}

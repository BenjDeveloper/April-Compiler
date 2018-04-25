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
#include "../include/errors.hpp"

//----------------------------
// Errors :: [21-30] node -> expression -> Assignment
extern april::STRUCINFO* april_errors;

namespace april
{
    llvm::Value* Assignment::codeGen(CodeGenContext& context)
    {
        if (context.searchVariable(lhs.name) == nullptr)
        {
			return Errors::call(context, 21, april_errors->file_name, april_errors->line, lhs.name);
        }
		llvm::Value* lhs_type = lhs.codeGen(context);
        if (rhs_value != nullptr) 
        { 
			if (lhs_type->getType() != rhs_value->getType())
			{
				return Errors::call(context, 23, april_errors->file_name, april_errors->line, lhs.getName());
			}
            return new llvm::StoreInst(rhs_value, context.locals()[lhs.name], false, context.currentBlock());
        }
        else 
        { 
            llvm::Value* expr_value = rhs.codeGen(context);
            if (expr_value == nullptr)
            {
				return Errors::call(context, 22, april_errors->file_name, april_errors->line, "");
            }

			if (lhs_type->getType() != expr_value->getType())
			{
				return Errors::call(context, 23, april_errors->file_name, april_errors->line, lhs.getName());
			}

            return new llvm::StoreInst(expr_value, context.locals()[lhs.name], false, context.currentBlock()); 
        }
    }
}

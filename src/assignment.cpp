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
        if (context.searchVariable(lhs.name) == nullptr)
        {
            printError(">>la variable '"+lhs.name+"' no ha sido declarada\n");
            context.addError();
            return nullptr;
        }

        if (rhs_value != nullptr) 
        { 
            return new llvm::StoreInst(rhs_value, context.locals()[lhs.name], false, context.currentBlock());
        }
        else 
        { 
            llvm::Value* expr_value = rhs.codeGen(context);
            if (expr_value == nullptr)
            {
                printError("la expresion es incorrecta\n");
                context.addError();
                return nullptr;
            }
            return new llvm::StoreInst(expr_value, context.locals()[lhs.name], false, context.currentBlock()); 
        }
    }
}

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
        
        return new llvm::StoreInst(rhs.codeGen(context), context.locals()[lhs.name], false, context.currentBlock());
    }
}
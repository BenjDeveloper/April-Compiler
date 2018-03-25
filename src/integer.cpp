#include <iostream>
#include "../include/integer.hpp"
#include "../include/codegencontext.hpp"
//----------------------------
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/IRBuilder.h"

namespace april
{
    llvm::Value* Integer::codeGen(CodeGenContext& context)
    {
        return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context.getGlobalContext()), value, true);
    }
}

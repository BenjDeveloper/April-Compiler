#include <iostream>
#include "../include/double.hpp"
#include "../include/codegencontext.hpp"
//----------------------------
#include "llvm/IR/IRBuilder.h"

namespace april
{
    llvm::Value* Double::codeGen(CodeGenContext& context)
    {
        return llvm::ConstantFP::get(llvm::Type::getDoubleTy(context.getGlobalContext()), value);
    }
}

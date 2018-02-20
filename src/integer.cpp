#include <iostream>
#include "../include/integer.hpp"

//----------------------------
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/IRBuilder.h"

namespace april
{
    llvm::Value* Integer::codeGen(CodeGenContext& context)
    {
        //std::cout << "Integer creado: " << value << std::endl;
        return llvm::ConstantInt::get(llvm::Type::getInt64Ty(llvm::getGlobalContext()), value, true);
    }
}

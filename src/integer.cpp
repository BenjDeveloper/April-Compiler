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
        // if (value == 0 or value == 1) { return llvm::ConstantInt::get(llvm::Type::getInt1Ty(llvm::getGlobalContext()), value, true); }
        // else if (value >= 2 &&  value <= 254) { return llvm::ConstantInt::get(llvm::Type::getInt8Ty(llvm::getGlobalContext()), value, true); }
        // else if (value >= 256 &&  value < 32767) { return llvm::ConstantInt::get(llvm::Type::getInt16Ty(llvm::getGlobalContext()), value, true); }
        // else if (value >= -2147483648 &&  value < 2147483647) { return llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvm::getGlobalContext()), value, true); }
        return llvm::ConstantInt::get(llvm::Type::getInt64Ty(llvm::getGlobalContext()), value, true);
    }
}

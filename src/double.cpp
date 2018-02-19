#include <iostream>
#include "../include/double.hpp"

//----------------------------
#include "llvm/IR/IRBuilder.h"

namespace april
{
    llvm::Value* Double::codeGen(CodeGenContext& context)
    {
        //std::cout << "Double creado: " << value << std::endl;
        return llvm::ConstantFP::get(llvm::Type::getDoubleTy(llvm::getGlobalContext()), value);
    }
}

#include <iostream>
#include "../include/boolean.hpp"

namespace april
{
    Boolean::Boolean(std::string str_value)
    {
        this->str_value = str_value;
        int_value = (str_value == "true")?(1):(0);
    }

    llvm::Value* Boolean::codeGen(CodeGenContext& context)
    {
        return llvm::ConstantInt::get(llvm::Type::getInt1Ty(context.getGlobalContext()), int_value);
    }
}
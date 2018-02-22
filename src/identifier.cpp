#include <iostream>
#include "../include/identifier.hpp"
#include "../include/codegencontext.hpp"

namespace april
{
    llvm::Value* Identifier::codeGen(CodeGenContext& context)
    {
        if (context.searchVariable(name) == nullptr)
        {
            printError("la variable '"+name+"' no ha sido declarada\n");
            context.addError();
            return nullptr;
        }
        return new llvm::LoadInst(context.locals()[name], "", false, context.currentBlock());
    }
}
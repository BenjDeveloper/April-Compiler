#include <iostream>
#include "../include/identifier.hpp"
#include "../include/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    llvm::Value* Identifier::codeGen(CodeGenContext& context)
    {
        if (context.searchVariable(name) == nullptr)
        {
            printError(april_errors->file_name+": "+std::to_string(april_errors->line)+" error: la variable '"+name+"' no ha sido declarada\n");
            context.addError();
            return nullptr;
        }
        return new llvm::LoadInst(context.locals()[name], "", false, context.currentBlock());
    }
}
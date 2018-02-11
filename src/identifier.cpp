#include <iostream>
#include "../include/identifier.hpp"
#include "../include/codegencontext.hpp"

namespace april
{
    llvm::Value* Identifier::codeGen(CodeGenContext& context)
    {
        std::cout << "Identificador creado: " << name << std::endl;

        if (context.locals().find(name) == context.locals().end())
        {
            std::cout << "la variable no ha sido declarada" << std::endl;
            return NULL;
        }
        return new llvm::LoadInst(context.locals()[name], "", false, context.currentBlock());
    }
}
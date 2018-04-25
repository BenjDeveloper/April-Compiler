#include <iostream>
#include "../include/identifier.hpp"
#include "../include/codegencontext.hpp"
#include "../include/errors.hpp"

//----------------------------
// Errors :: [141-150] node -> expression -> Identifier
extern april::STRUCINFO* april_errors;

namespace april
{
    llvm::Value* Identifier::codeGen(CodeGenContext& context)
    {
        if (context.searchVariable(name) == nullptr)
        {
			return Errors::call(context, 141, april_errors->file_name, april_errors->line, name);
        }
        return new llvm::LoadInst(context.locals()[name], "", false, context.currentBlock());
    }
}
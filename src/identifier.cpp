#include <iostream>
#include "../include/identifier.hpp"
#include "../include/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    llvm::Value* Identifier::codeGen(CodeGenContext& context)
    {
        if (context.searchVariableAll(name) == nullptr)
        {
            printError(april_errors->file_name+": "+std::to_string(april_errors->line)+" error: la variable '"+name+"' no ha sido declarada.\n");
            context.addError();
            return nullptr;
        }
		if (context.map_struct_type.find(name) != context.map_struct_type.end())
		{
			std::cout << "APRIL" << std::endl;
			return new llvm::LoadInst(context.map_struct_type[name], "", false, context.currentBlock());
		}	
		else
			return new llvm::LoadInst(context.searchVariableAll(name), "", false, context.currentBlock());
    }
}
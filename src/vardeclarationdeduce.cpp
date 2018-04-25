#include "../include/vardeclarationdeduce.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"
#include "../include/errors.hpp"

//----------------------------
// Errors :: [11-20] node -> statemente -> vardeclarationdeduce
extern april::STRUCINFO* april_errors;

namespace april
{
    llvm::Value* VariableDeclarationDeduce::codeGen(CodeGenContext& context)
    {
        if (context.searchVariable(id.name))
        {
			return Errors::call(context, 11, april_errors->file_name, april_errors->line, id.getName());
        }
        
        llvm::Value* expr_value = expr->codeGen(context);

        if (expr_value == nullptr)
        {
			return Errors::call(context, 12, april_errors->file_name, april_errors->line, id.getName());
        }
        
        llvm::AllocaInst* alloc = new llvm::AllocaInst(expr_value->getType(), id.name.c_str(), context.currentBlock());
        context.locals()[id.name] = alloc;
        Assignment assn(id, *expr, expr_value);
        
        auto val = assn.codeGen(context);
        if (val == nullptr)
        {
			return Errors::call(context, 13, april_errors->file_name, april_errors->line, id.getName());
        }

        return val;
    }
}
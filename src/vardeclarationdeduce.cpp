#include "../include/vardeclarationdeduce.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    llvm::Value* VariableDeclarationDeduce::codeGen(CodeGenContext& context)
    {
        if (context.searchVariableAll(id.name))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '"+id.name+"' ya existe\n");
            context.addError();
            return nullptr;
        }
        
        llvm::Value* expr_value = expr->codeGen(context);

        if (expr_value == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '"+id.name+"' no se pudo inicializar ya que la expresion es incorrecta\n");
            context.addError();
            return nullptr;
        }
        
        llvm::AllocaInst* alloc = new llvm::AllocaInst(expr_value->getType(), id.name.c_str(), context.currentBlock());
        context.locals()[id.name] = alloc;
		context.setVarType("var", id.getName());

        Assignment assn(id, *expr, expr_value);
        
        auto val = assn.codeGen(context);
        if (val == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la asignacion a '"+id.name+"' es vacia\n");
            context.addError();
            return nullptr;
        }

        return val;
    }
}
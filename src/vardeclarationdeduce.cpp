#include "../include/vardeclarationdeduce.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"

namespace april
{
    llvm::Value* VariableDeclarationDeduce::codeGen(CodeGenContext& context)
    {
        
        if (context.searchVariable(id.name))
        {
            printError("la variable '"+id.name+"' ya existe\n");
            context.addError();
            return nullptr;
        }
        
        llvm::Value* expr_value = expr->codeGen(context);
        if (expr_value == nullptr)
        {
            printError("la variable '"+id.name+"' no se pudo inicializar ya que la expresion es incorrecta\n");
            context.addError();
            return nullptr;
        }

        llvm::AllocaInst* alloc = new llvm::AllocaInst(expr_value->getType(), id.name.c_str(), context.currentBlock());
        context.locals()[id.name] = alloc;
        Assignment assn(id, *expr, expr_value);
        
        auto val = assn.codeGen(context);
        if (val == nullptr)
        {
            printError("la asignacion a '"+id.name+"' es vacia\n");
            context.addError();
            return nullptr;
        }
        return val;
    }
}
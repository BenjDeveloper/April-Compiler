#include "../headers/foriteration.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    ForIteration::~ForIteration()
    {
        if (ident != nullptr)
        {
            delete ident;
            ident = nullptr;
        }

        if (expr != nullptr)
        {
            delete expr;
            expr = nullptr;
        }

        if (block != nullptr)
        {
            delete block;
            block = nullptr;
        }
    }

    Symbol* ForIteration::codeGen(CodeGenContext& context)
    {
        Symbol* sym_expr = expr->codeGen(context);
        if (sym_expr == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: expresion nula en el bucle for.\n");
            context.addError();
            return nullptr;
        }
        if (sym_expr->type != Type::LIST)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la expresion debe ser iterable.\n");
            context.addError();
            return nullptr;
        }

        Symbol* result = nullptr;
        
        block->type_scope = BlockScope::FOR;
        block->prev = context.getCurrentBlock();
        context.setCurrentBlock(block);
       
        ident->codeGen(context);
        Symbol* sym_ident = context.findIdentLocals(ident->getName());
        if (sym_ident == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: tmp nula.\n");
            context.addError();
            return nullptr;
        }
        Symbol* sym_tmp = sym_expr->prox;
        while (sym_tmp != nullptr && !block->stop)
        {
            sym_ident->type = sym_tmp->type;
            sym_ident->value = sym_tmp->value;

            result = block->codeGen(context);
            if (result == nullptr)
                return nullptr;
                
            sym_tmp = sym_tmp->prox;
        }

        block->stop = false;
        context.popCurrentBlock();
        // if (result == nullptr)
        //     std::cout << "result es NULO (FOR)" << std::endl;
        // else
        //     std::cout << "result (FOR): " << *result << std::endl;

        return result; 
    }
}
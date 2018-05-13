#include "../headers/listaccess.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    ListAccess::~ListAccess()
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

        if (expr_index != nullptr)
        {
            delete expr_index;
            expr_index = nullptr;
        }
    }

    Symbol* ListAccess::codeGen(CodeGenContext& context)
    {       
        if (ident == nullptr && expr == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: ident y expr no definidos.\n");
            context.addError();
            return nullptr;
        }

        if (ident != nullptr && !context.existIdenLocals(ident->getName()))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '"+ident->getName()+"' no existe.\n");
            context.addError();
            return nullptr;
        }
        
        Symbol* sym_index = expr_index->codeGen(context);
        if (sym_index == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: expresion nula como indice de la lista.\n");
            context.addError();
            return nullptr;
        }
        if (sym_index->type != Type::INTEGER)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: tipo de expresion diferente a 'integer' como indice en la lista.\n");
            context.addError();
            return nullptr;
        }

        Symbol* sym_list = nullptr;
        
        if (ident != nullptr)
            sym_list = context.findIdentLocals(ident->getName());
        else
            sym_list = expr->codeGen(context);

        if (sym_list == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: expresion nula.\n");
            context.addError();
            return nullptr;
        }


        if (sym_list->down != nullptr)
        {
            sym_list = sym_list->down;
            std::cout << "AQUI" << std::endl;
        }

        int cont = 0;
        int index = sym_index->value._ival;
        Symbol* aux = sym_list->prox;
        
        for ( ; cont < index && aux != nullptr ; cont++ )
            aux = aux->prox;

        // std::cout << "cont: " << cont << std::endl;
        if (aux == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: index fuera del rango de la lista.\n");
            context.addError();
            return nullptr;
        }

        if (aux->down != nullptr)
            aux = aux->down;

        return aux;
    }
};
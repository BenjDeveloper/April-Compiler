#include "../headers/methodhandlelist.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/funclist.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    MethodHandleList::~MethodHandleList()
    {
        //falta limpieza de punteros... :(
    }

    Symbol* MethodHandleList::codeGen(CodeGenContext& context)
    {
        Symbol* tmp = nullptr;
        if (ident_method->getName() == "size")
        {
            if (args->size() == 0)
                tmp = list::size(sym_expr);
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numero de parametros incorrectos en la llamada del metodo '"+ident_method->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
        }        
        else if (ident_method->getName() == "append")
        {
            if (args->size() == 1)
            {
                Symbol* sym = (*args)[0]->codeGen(context);
                tmp = list::append(sym_expr, sym);
            }
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numero de parametros incorrectos en la llamada del metodo '"+ident_method->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
        } 
        else if (ident_method->getName() == "index")
        {
            if (args->size() == 1)
            {
                Symbol* sym = (*args)[0]->codeGen(context);
                tmp = list::index(sym_expr, sym);
            }
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numero de parametros incorrectos en la llamada del metodo '"+ident_method->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
        }
        else if (ident_method->getName() == "remove")
        {
            if (args->size() == 1)
            {
                Symbol* sym = (*args)[0]->codeGen(context);
                tmp = list::remove(sym_expr, sym);
            }
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numero de parametros incorrectos en la llamada del metodo '"+ident_method->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
        }
        else
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el nombre '"+ident_method->getName()+"' no esta definida como metodo en tipo list.\n");
            context.addError();
            return nullptr;
        }

        return tmp;
    }
}
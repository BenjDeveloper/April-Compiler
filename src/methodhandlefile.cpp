#include "../headers/methodhandlefile.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/funclist.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    MethodHandleFile::~MethodHandleFile()
    {
        //falta limpieza de punteros... :(
    }

    Symbol* MethodHandleFile::codeGen(CodeGenContext& context)
    {
        Symbol* tmp = nullptr;

        if (ident_method->getName() == "close")
        {
            if (args->size() == 0)
                tmp = file::close(sym_expr);
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numero de parametros incorrectos en la llamada del metodo '"+ident_method->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
        }
        else if (ident_method->getName() == "is_open")
        {
            if (args->size() == 0)
                tmp = file::is_open(sym_expr);
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numero de parametros incorrectos en la llamada del metodo '"+ident_method->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
        }
        else if (ident_method->getName() == "write")
        {
            if (args->size() == 1)
            {
                Symbol* str = (*args)[0]->codeGen(context);
                if (str->type != Type::STRING)
                {
                    printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: tipos de parametros incorrectos en la llamada del metodo '"+ident_method->getName()+"'.\n");
                    context.addError();
                    return nullptr;
                }
                tmp = file::write(sym_expr, *str->value._sval);
            }
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numero de parametros incorrectos en la llamada del metodo '"+ident_method->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
        }
        else if (ident_method->getName() == "readline")
        {
            if (args->size() == 0)
                tmp = file::readline(sym_expr);
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numero de parametros incorrectos en la llamada del metodo '"+ident_method->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
        }
        else if (ident_method->getName() == "is_eof")
        {
            if (args->size() == 0)
                tmp = file::is_eof(sym_expr);
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numero de parametros incorrectos en la llamada del metodo '"+ident_method->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
        }
        else
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el nombre '"+ident_method->getName()+"' no esta definida como metodo en tipo stream.\n");
            context.addError();
            return nullptr;
        }

        return tmp;
    }
}
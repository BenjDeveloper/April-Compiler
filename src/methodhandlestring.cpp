#include "../headers/methodhandlestring.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/funclist.hpp"

extern april::STRUCINFO* april_errors;


namespace april
{
    MethodHandleString::~MethodHandleString()
    {

    }

    Symbol* MethodHandleString::codeGen(CodeGenContext& context)
    {
        Symbol* tmp = nullptr;
        if (ident_method->getName() == "size")
        {
            if (args->size() == 0)
                tmp = string::size(sym_expr);
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numero de parametros incorrectos en la llamada del metodo '"+ident_method->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
        } 
        else
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el nombre '"+ident_method->getName()+"' no esta definida como metodo en el tipo string.\n");
            context.addError();
            return nullptr;
        }

        return tmp;
    }
}
#include "../headers/methodhandleIo.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/funclist.hpp"

extern april::STRUCINFO* april_errors;


namespace april
{
    MethodHandleIo::~MethodHandleIo()
    {

    }

    Symbol* MethodHandleIo::codeGen(CodeGenContext& context)
    {
        // if (ident_method->getName() == "input")
        // {
        //     if (args->size() == 0)
        //         return io::input();
        //     else
        //     {
        //         printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: este metodo no requiere entrada de parametros.\n");
        //         context.addError();
        //         return nullptr;
        //     }
        // }

        if (args->size() == 0 || args->size() > 1)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numeros de parametros incorrectos '"+ident_method->getName()+"' .\n");
            context.addError();
            return nullptr;
        }

        Symbol* tmp = nullptr;
        Expression* expr_arg = nullptr;
        Symbol* sym_arg = sym_arg = (*args)[0]->codeGen(context);
    
        if (sym_arg == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: en el pase de parametros '"+ident_method->getName()+"'.\n");
            context.addError();
            return nullptr;
        }

        if (sym_arg->type == Type::LIST || sym_arg->type == Type::LIST_DOWN || sym_arg->type == Type::UNDEFINED)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: no se puede convertir el tipo de dato del parametro '"+ident_method->getName()+"'.\n");
            context.addError();
            return nullptr;
        }

        if (ident_method->getName() == "println")
        {
            tmp = io::println(sym_arg);
        } 
        else if (ident_method->getName() == "print")
        {
            tmp = io::print(sym_arg);
        }
        else
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el nombre '"+ident_method->getName()+"' no esta definida.\n");
            context.addError();
            return nullptr;
        }

        return tmp;
    }
}
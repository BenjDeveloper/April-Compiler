#include "../headers/methodhandlecast.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/funclist.hpp"

extern april::STRUCINFO* april_errors;


namespace april
{
    MethodHandleCast::~MethodHandleCast()
    {

    }

    Symbol* MethodHandleCast::codeGen(CodeGenContext& context)
    {
        Expression* expr_arg = nullptr;
        if (args->size() == 1)
            expr_arg = args->back();
        else
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numero de parametros incorrectos en la llamada del metodo '"+ident_method->getName()+"'.\n");
            context.addError();
            return nullptr;
        }

        Symbol* sym_arg = expr_arg->codeGen(context);
        
        if (sym_arg == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: no se puede convertir el tipo de dato - apuntador nullo.\n");
            context.addError();
            return nullptr;
        }
        
        if (sym_arg->type == Type::BOOLEAN || sym_arg->type == Type::LIST || sym_arg->type == Type::LIST_DOWN || sym_arg->type == Type::UNDEFINED)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: no se puede convertir el tipo de dato del parametro.\n");
            context.addError();
            return nullptr;
        }

        if (ident_method->getName() != "toString" && (sym_arg->type == Type::STRING  &&  !(string::isNumber(sym_arg))))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: no se puede castear letras a numeros.\n");
            context.addError();
            return nullptr;
        }

        Symbol* tmp = nullptr;
        if (ident_method->getName() == "toDouble")
        {
            tmp = cast::toDouble(sym_arg);
        } 
        else if (ident_method->getName() == "toString")
        {
            tmp = cast::toString(sym_arg);
        }
        else if (ident_method->getName() == "toInt")
        {
            if (sym_arg->type != Type::DOUBLE)
                tmp = cast::toInt(sym_arg);
            else    
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: toInt(arg); no castea un 'arg' de tipo Double a int.\n");
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
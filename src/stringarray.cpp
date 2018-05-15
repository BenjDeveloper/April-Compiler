#include "../headers/stringarray.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;


namespace april
{
    Symbol* StringArray::codeGen(CodeGenContext& context)
    {

        Symbol* sym_ident = context.findIdentLocals(ident_var->getName());
        //std::cout <<"stringArray (sym_ident)- > "<< *sym_ident << std::endl;
        if (!(sym_ident))
        {
            // el variable no existe
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el variable no existe\n");
            context.addError();
            return nullptr;
        }
        if (sym_ident->type != Type::STRING)
        {
            // error de argumento en el array
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable no es de tipo string \n");
            context.addError();
            return nullptr;
        }

        Symbol* sym_indice =  expr_indice->codeGen(context);
        // std::cout <<"stringArray (sym_indice)- > "<< *sym_indice << (sym_ident->value._sval)->length() << std::endl;
        if (sym_indice->type != Type::INTEGER)
        {
            // error de argumento en el array
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error:error de argumento en el array \n");
            context.addError();
            return nullptr;
        }

        if (sym_indice->value._ival > (sym_ident->value._sval)->length())
        {
            // error de desbordamiento de indice 
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: desbordamiento de indice  \n");
            context.addError();
            return nullptr;
        }

        std::string arr = *(sym_ident->value._sval);
        arr = arr[sym_indice->value._ival];

        Symbol* tmp = new Symbol();
        tmp->name = "";
        tmp->type = Type::STRING;
        tmp->value._sval = new std::string(arr);
        tmp->is_constant = true;
        tmp->is_variable = false;
        // std::cout <<"stringArray - > "<< *tmp << std::endl;
        return tmp;
    };
}
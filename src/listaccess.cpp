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
        std::cout << "List Access" << std::endl;
        if (!context.existIdenLocals(ident->getName()))
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

        Symbol*& sym_list = context.findIdentLocals(ident->getName());
        int index = sym_index->value._ival;
        std::cout << "index: " << index << std::endl;
        int cont = -1;
        Symbol* aux = sym_list;
        
        for ( ; cont < index && aux != nullptr ; cont++ )
        {
            aux = aux->prox;
        }
        std::cout << "cont: " << cont << std::endl;
        std::cout << "aux->value._ival" << aux->value._ival << std::endl;

        return aux;
    }
};
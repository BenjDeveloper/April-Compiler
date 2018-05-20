#include <iostream>
#include "../headers/methodcall.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/methodhandlecast.hpp"
#include "../headers/funclist.hpp"
#include "../headers/methodhandleio.hpp"

extern april::STRUCINFO* april_errors;

namespace april 
{
    Symbol* MethodCall::codeGen(CodeGenContext& context)
    {

        if (ident->getName() == "println" || ident->getName() == "print" || ident->getName() == "input")
        {
            MethodHandleIo* tmp = new MethodHandleIo(ident,args);
            Symbol* symbol = tmp->codeGen(context);
            delete tmp;
            tmp = nullptr;
            context.getCurrentBlock()->vars_tmp.push_back(symbol);
            
            return symbol;
        }
        else if (ident->getName() == "toDouble" || ident->getName() == "toInt" || ident->getName() == "toString")
        {
            MethodHandleCast* tmp = new MethodHandleCast(ident,args);
            Symbol* symbol = tmp->codeGen(context);
            delete tmp;
            tmp = nullptr;
            context.getCurrentBlock()->vars_tmp.push_back(symbol);
            
            return symbol;
        }
        else if (ident->getName() == "open")
        {
            if (args->size() == 2)
            {
                Symbol* name = (*args)[0]->codeGen(context);
                Symbol* type = (*args)[1]->codeGen(context);
                if (name->type != Type::STRING || type->type != Type::STRING)
                {
                    printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: tipos de parametros incorrectos en la llamada del metodo '"+ident->getName()+"'.\n");
                    context.addError();
                    return nullptr;
                }

                Symbol* tmp = file::open(*name->value._sval, *type->value._sval);
                context.getCurrentBlock()->vars_tmp.push_back(tmp);
                return tmp;
            }
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numero de parametros incorrectos en la llamada del metodo '"+ident->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------

        if (!context.existFunction(ident->getName()))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la funcion '"+ident->getName()+"'no existe.\n");
            context.addError();
            return nullptr;
        }

        if (args->size() != context.getFunctions()[ident->getName()]->getArgs()->size())
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el numero de parametros no coinciden con la llamada a la funcion '"+ident->getName()+"'.\n");
            context.addError();
            return nullptr;
        }


        //----------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------

        if (context.getFunctions()[ident->getName()]->getBlock() == context.getCurrentBlock())
        {
            std::cout << "Es recursivo bitches!!" << std::endl;
        }
        else
        {
            std::cout << "NO es una llamada recursiva" << std::endl;
        }

        //----------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------


        VarList*& var_list = context.getFunctions()[ident->getName()]->getArgs();
        ExpressionList::iterator ite_args = args->begin();
        VarList::iterator ite_para_fn = var_list->begin();
        Symbol* sym_0 = nullptr;
        Symbol* sym_1 = nullptr;

        while (ite_args != args->end())
        {
            sym_0 = (*ite_args)->codeGen(context);
            context.scope_type = Scope::FUNCTION;
            context.setCurrentFunction(context.getFunctions()[ident->getName()]);
            sym_1 = (*ite_para_fn)->codeGen(context);
            context.scope_type = Scope::BLOCK;
            context.setCurrentFunction(nullptr);
            
            if (sym_0 == nullptr || sym_1 == nullptr)
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: en codegen de methodcall.\n");
                context.addError();
                return nullptr;
            }

            if ((sym_0->type != sym_1->type) && !(sym_0->type == Type::INTEGER && sym_1->type == Type::DOUBLE)) //FALTA VALIDAR DOUBLE
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el tipo de parametros no coinciden con la llamada a la funcion '"+ident->getName()+"'.\n");
                context.addError();
                return nullptr;
            }

            if (sym_0->type != Type::LIST)
                sym_1->value = sym_0->value; 
            else
            {
                sym_1->prox = sym_0->prox;
                sym_1->down = sym_0->down;
                sym_1->in_list = true;
            }

            ite_args++;
            ite_para_fn++;
        }
        
        Symbol* sym = context.getFunctions()[ident->getName()]->runCode(context);
        // std::cout << "fin methodcall" << std::endl;
        return sym;
    }
}
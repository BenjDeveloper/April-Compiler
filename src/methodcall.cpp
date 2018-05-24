#include <iostream>
#include "../headers/methodcall.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/methodhandlecast.hpp"
#include "../headers/funclist.hpp"
#include "../headers/methodhandleio.hpp"

extern april::STRUCINFO* april_errors;

namespace april 
{
    MethodCall::~MethodCall()
    {
    }

    Symbol* MethodCall::codeGen(CodeGenContext& context)
    {
        if (ident->getName() == "println" || ident->getName() == "print" || ident->getName() == "input")
        {
            MethodHandleIo* method_handle_io = new MethodHandleIo(ident,args);
            Symbol* tmp = method_handle_io->codeGen(context);
            if (tmp == nullptr)
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: expresion nula en la llamada del metodo '"+ident->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
            delete method_handle_io;
            method_handle_io = nullptr;
            context.getCurrentBlock()->locals.push_back(tmp);

            return tmp;
        }
        else if (ident->getName() == "double" || ident->getName() == "int" || ident->getName() == "str")
        {
            MethodHandleCast* mothod_handle_cast = new MethodHandleCast(ident,args);
            Symbol* tmp = mothod_handle_cast->codeGen(context);
            if (tmp == nullptr)
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: expresion nula en la llamada del metodo '"+ident->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
            delete mothod_handle_cast;
            mothod_handle_cast = nullptr;
            // context.getCurrentBlock()->locals.push_back(tmp);
            
            return tmp;
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
                // context.getCurrentBlock()->locals.push_back(tmp);
                
                return tmp;
            }
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: numero de parametros incorrectos en la llamada del metodo '"+ident->getName()+"'.\n");
                context.addError();
                return nullptr;
            }
        }
        else if (ident->getName() == "range")
        {
            if (args->size() == 1)
            {
                Symbol* last = (*args)[0]->codeGen(context);
                if (last->type != Type::INTEGER)
                {
                    printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: tipos de parametros incorrectos en la llamada del metodo '"+ident->getName()+"'.\n");
                    context.addError();
                    return nullptr;
                }
                Symbol* tmp = lib::range(last);
                // context.getCurrentBlock()->locals.push_back(tmp); //OJO--> la lista si no se le asigna a una variable queda colgando en RAM
                
                return tmp;
            }
            else if (args->size() == 2)
            {
                Symbol* first = (*args)[0]->codeGen(context);
                Symbol* last = (*args)[1]->codeGen(context);
                if (first->type != Type::INTEGER || last->type != Type::INTEGER)
                {
                    printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: tipos de parametros incorrectos en la llamada del metodo '"+ident->getName()+"'.\n");
                    context.addError();
                    return nullptr;
                }
                Symbol* tmp = lib::range(first, last);
                // context.getCurrentBlock()->locals.push_back(tmp);//OJO-->la lista si no se le asigna a una variable queda colgando en RAM

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

        if (context.getStackFunc() != nullptr && context.getStackFunc()->top()->getName() == ident->getName())
        {
            Identifier* tmp_ident = context.getStackFunc()->top()->getIdent();
            VarList* tmp_var_list = context.getStackFunc()->top()->getArgs();
            Block* tmp_block =  context.getStackFunc()->top()->getBlock();
            context.getStackFunc()->push(new Function{tmp_ident, tmp_var_list, tmp_block, true});
        }
        else
        {
            if (context.getStackFunc() == nullptr) 
                context.getStackFunc() = new std::stack<Function*>();

            context.getStackFunc()->push(context.getFunctions()[ident->getName()]);
        }

        //----------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------
        VarList* var_list = context.getFunctions()[ident->getName()]->getArgs();
        ExpressionList::iterator ite_args = args->begin();
        VarList::iterator ite_para_fn = var_list->begin();
        Symbol* sym_0 = nullptr;
        Symbol* sym_1 = nullptr;

        while (ite_args != args->end())
        {
            sym_0 = (*ite_args)->codeGen(context);
            
            context.scope_type = Scope::FUNCTION;
            context.setCurrentFunction(context.getStackFunc()->top());
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
        
        Symbol* sym = context.getStackFunc()->top()->runCode(context);

        if (sym == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el sym es igual a nulo en la llamada de la funcion '"+ident->getName()+"'.\n");
            context.addError();
            return nullptr;
        }
        
        if (context.getStackFunc() != nullptr && !context.getStackFunc()->empty())
        {
            if (context.getStackFunc()->top()->getName() == ident->getName() && context.getStackFunc()->size() > 1)
            {
                // std::cout << "antes eliminando... " << context.getStackFunc()->top()->getName() << std::endl;
                if (context.getStackFunc()->top()->isTmp())
                {
                    Function* tmp_func = context.getStackFunc()->top();
                    delete tmp_func;
                    tmp_func = nullptr;
                } 
                context.getStackFunc()->pop();
            }
            else if (context.getStackFunc()->size() == 1)
            {
                // std::cout << "eliminando... " << ident->getName() << std::endl;
                context.getStackFunc()->pop();
                delete context.getStackFunc();                
                context.getStackFunc() = nullptr;
            }
        }
        // std::cout << "sym: " << sym->value._ival << std::endl;
        return sym;
    }
}
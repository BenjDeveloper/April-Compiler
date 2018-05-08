#include "../headers/methodcall.hpp"
#include "../headers/codegencontext.hpp"
#include <iostream>

extern april::STRUCINFO* april_errors;

namespace april 
{
    Symbol* MethodCall::codeGen(CodeGenContext& context)
    {
        if (ident->getName() != "println")
        {
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

            VarList*& var_list = context.getFunctions()[ident->getName()]->getArgs();
            ExpressionList::iterator ite_args = args->begin();
            VarList::iterator ite_para_fn = var_list->begin();
            Symbol* sym_0 = nullptr;
            Symbol* sym_1 = nullptr;

            //std::vector<Symbol*>& tmp_locals = context.getCurrentBlock()->locals;

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

                sym_1->value = sym_0->value; 
                //Symbol* sym_new = new Symbol{};
                //*sym_new = *sym_1;
                
                //context.getFunctions()[ident->getName()]->getLocals().push_back(sym_new);
                //context.getFunctions()[ident->getName()]->existIdenLocals(sym_1->name);
                //delete sym_0;
                //delete sym_1;

                ite_args++;
                ite_para_fn++;
            }

            Symbol* sym = context.getFunctions()[ident->getName()]->runCode(context);
            return sym;
        }
        
        for(Expression* expr: *args)
        {
            Symbol* tmp = expr->codeGen(context);
            if (tmp->is_variable)
                tmp = context.findIdentLocals(tmp->name);

            if (ident->getName() == "println")
                std::cout << ">> "<< *tmp << std::endl;
        }        
        return nullptr;
    }
}
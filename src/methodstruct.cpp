#include "../headers/methodstruct.hpp"
#include "../headers/methodhandle.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* MethodStruct::codeGen(CodeGenContext& context)
    {
        Symbol* sym_ident = nullptr;
        Symbol* symbol = nullptr;
        if (ident_var)
        {
            sym_ident = context.findIdentLocals(ident_var->getName());
            if (!(sym_ident))
            {
                // el variable no existe
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: variable no existe \n");
                context.addError();
                return nullptr;
            }

            if (!context.findMethods(ident_method->getName()))
            {
                // el metodo no ha sido declarado
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error:el metodo no ha sido declarado \n");
                context.addError();
                return nullptr;
            }

            MethodHandle* methodhandle = nullptr;
            if (sym_ident->type == Type::INTEGER)
                methodhandle = new MethodHandle(ident_var,ident_method, args, Type::INTEGER);
            
            else if (sym_ident->type == Type::DOUBLE)
                methodhandle = new MethodHandle(ident_var, ident_method, args, Type::DOUBLE);
            
            else if (sym_ident->type == Type::STRING)
                methodhandle = new MethodHandle(ident_var, ident_method, args, Type::STRING);
            
            else if (sym_ident->type == Type::BOOLEAN)
                methodhandle = new MethodHandle(ident_var, ident_method, args, Type::BOOLEAN);
            
            else
            {
                // error de tipo indefinido
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error:tipo indefinido \n");
                context.addError();
                return nullptr;
            }
            symbol = methodhandle->codeGen(context);
        }
        else if (expr_var)
        {
            sym_ident = expr_var->codeGen(context);
            //std::cout<< *sym_ident << std::endl;
            Identifier* tmp;
            MethodHandle* methodhandle = nullptr;
            if (sym_ident->type == Type::INTEGER)
                methodhandle = new MethodHandle(sym_ident,ident_method, args, Type::INTEGER);// SIN MANEJAR BIEN
            
            else if (sym_ident->type == Type::DOUBLE)
                methodhandle = new MethodHandle(sym_ident, ident_method, args, Type::DOUBLE);// SIN MANEJAR BIEN
            
            else if (sym_ident->type == Type::STRING)
                methodhandle = new MethodHandle(sym_ident, ident_method, args, Type::STRING);

            else if (sym_ident->type == Type::BOOLEAN)
                methodhandle = new MethodHandle(sym_ident, ident_method, args, Type::BOOLEAN);// SIN MANEJAR BIEN
            
            else
            {
                // error de tipo indefinido
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error:tipo indefinido \n");
                context.addError();
                return nullptr;
            }
            symbol = methodhandle->codeGen(context);
        }
        else
        {
            // error de interpretacion
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error:de interpretacion \n");
            context.addError();
            return nullptr;
        }
        
        return symbol;
    }

}

#include "../headers/methodstruct.hpp"
#include "../headers/methodhandle.hpp"
#include "../headers/codegencontext.hpp"

namespace april
{
    Symbol* MethodStruct::codeGen(CodeGenContext& context)
    {

        Symbol* sym_ident = context.findIdentLocals(ident_var->getName());
        if (!(sym_ident))
        {
            // el variable no existe
        }

        if (!context.findMethods(ident_method->getName()))
        {
            // el metodo no ha sido declarado
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
        }
        Symbol* sym_expr = methodhandle->codeGen(context);

        return sym_expr;
    }

}

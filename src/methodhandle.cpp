#include "../headers/methodhandle.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/string.hpp"

namespace april
{
    Symbol* MethodHandle::codeGen(CodeGenContext& context)
    {
        Symbol* sym_expr = new Symbol(); 
        sym_expr->name = "";
        sym_expr->is_constant = true;
        sym_expr->is_variable = false;

        if (sym_var==nullptr)
        {
            if (!context.findMethods(ident_method->getName()))
            {
                // el metodo no ha sido declarado
            }
        }

        if (type==Type::STRING)
        {
            if (ident_method->getName() == "len")
            {
                sym_expr->type = Type::INTEGER;
                if(sym_var==nullptr){
                    //sym_expr->value._ival = String(*(context.findIdentLocals(ident_var->getName())->value._sval)).len();
                    sym_expr->value._ival = context.findIdentLocals(ident_var->getName())->value._sval->length();
                 }else
                    sym_expr->value._ival =  sym_var->value._sval->length();
            }
        }
        else if (type==Type::INTEGER)
        {

        }
        else if (type==Type::DOUBLE)
        {

        }
        
        if (!sym_expr)
        {
            //error el manejador de metodos no logra manejar el metodo de el tipo de dato asociado Type::UNDEFINE
        }

        return sym_expr;
    }
}
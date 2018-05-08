#include "../headers/methodhandle.hpp"
#include "../headers/codegencontext.hpp"

namespace april
{
    Symbol* MethodHandle::codeGen(CodeGenContext& context)
    {
        Symbol* sym_expr = new Symbol(); 
        sym_expr->name = "";
        sym_expr->is_constant = true;
        sym_expr->is_variable = false;

        if (!context.findMethods(ident_method->getName()))
        {
            // el metodo no ha sido declarado
        }

        if (type==Type::STRING)
        {
            if (ident_method->getName() == "len")
            {
                sym_expr->type = Type::INTEGER;
                sym_expr->value._ival = context.findIdentLocals(ident_var->getName())->value._sval->length();
                
                std::string a = " a ";
                str::string b = " b ";
                str::string* aa = a;
                str::string* bb = b;
            
                if (aa != bb) std::cout<<"aa!=bb"<< std::endl;

                if (aa->c_str() != bb->c_str()) std::cout<<"aa->c_str() != bb->c_str()"<< std::endl;
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
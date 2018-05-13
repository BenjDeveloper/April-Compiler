#include "../headers/assignmentlist.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    AssignmentList::~AssignmentList()
    {
        
    }

    Symbol* AssignmentList::codeGen(CodeGenContext& context)
    {
        if (expr == nullptr || expr_assig == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: no se puede establecer la asignacion, expresion nula.\n");
            context.addError();
            return nullptr;
        }

        Symbol* sym_expr = expr->codeGen(context);
        Symbol* sym_assig = expr_assig->codeGen(context);

        if (sym_expr->down != nullptr)
        {
            Symbol* aux = sym_expr;
            aux = aux->down;
            Symbol* tmp = nullptr;
            while (aux != nullptr)
            {
                tmp = aux;
                aux = aux->prox;
                delete tmp;
            }
            sym_expr->down = nullptr;
        }
        
        sym_expr->type = sym_assig->type;
        sym_expr->value = sym_assig->value;
        
        if (sym_expr->type == Type::LIST)
            sym_expr->down = sym_assig;

        return sym_expr;
    }
}
#include "../headers/list.hpp"
#include "../headers/codegencontext.hpp"

namespace april
{
    List::~List()
    {
        // std::cout << "destructor lista" << std::endl;
        for (Expression* expr : *expressions)
        {
            delete expr;
            expr = nullptr;
        }
    }

    Symbol* List::codeGen(CodeGenContext& context)
    {
        Symbol* root = new Symbol{};
        root->in_list = true;
        root->type = Type::LIST;
        Symbol* aux = root;

        for (Expression* expr : *expressions)
        {
            Symbol* tmp = expr->codeGen(context);
            if (tmp->type == Type::LIST)
            {
                aux->prox = new Symbol{};
                aux = aux->prox;
                aux->type = Type::LIST_DOWN;
                aux->down = tmp;
            }
            else
            {
                Symbol* _new = new Symbol{};
                _new->name = "";
                _new->type = tmp->type;
                _new->value = tmp->value;
                _new->is_constant = true;
                _new->is_variable = false;
                _new->in_list = true;
                aux->prox = _new;
                aux = aux->prox;
            }
        }

        return root;
    }
}
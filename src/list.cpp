#include "../headers/list.hpp"
#include "../headers/codegencontext.hpp"

namespace april
{
    List::~List()
    {
        std::cout << "destructor lista" << std::endl;
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
            Symbol* _new = new Symbol{};
            _new->name = "";
            _new->type = tmp->type;
            _new->value = tmp->value;
            _new->is_constant = true;
            _new->is_variable = false;
            _new->in_list = true;

            if (tmp->type == Type::LIST)
            {
                _new->prox = tmp->prox;
                _new->down = tmp->down;
                aux->prox = new Symbol{};
                aux = aux->prox;
                aux->down = _new;
            }
            else
            {
                aux->prox = _new;
                aux = aux->prox;
            }
        }

        return root;
    }
}
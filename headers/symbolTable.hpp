#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

namespace symbolTable
{
    struct node
    {
        const char *name;
        char type; // INT - i, FLOAT - f
        node *prox;
        union
        {
            int _int;
            float _float;
        } value;
      
    };

    node* push(node* &, node &);
    node* search(node* &, const char*);
    void clean(node* &);
}

#endif //SYMBOLTABLE_HPP

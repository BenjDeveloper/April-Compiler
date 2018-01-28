#include <cstring>
#include "../headers/symbolTable.hpp"

symbolTable::node* symbolTable::push(node* &table, node &element)
{
    char* name = new char[std::strlen(element.name)+1];
    std::strcpy(name, element.name);

    node* result = nullptr;
    if (table == nullptr)
    {
        table = new node{name, element.type, nullptr};
        result = table;
    }
    else
    {
        node* aux_table = table;
        while (aux_table->prox != nullptr) { aux_table = aux_table->prox; }

        aux_table->prox = new node{name, element.type, nullptr};
        result = aux_table->prox;
    }

    if (element.type == 'i'){ result->value._int = element.value._int; }
    else if (element.type == 'i'){ result->value._int = element.value._float; }

    return result;
}

symbolTable::node* symbolTable::search(node* &table, const char* name )
{
    node* aux_table = table;
    if (table != nullptr)
    {
        while (aux_table != nullptr && strcmp(aux_table->name, name) != 0) { aux_table = aux_table->prox; }
    }

    return aux_table;
}

void symbolTable::clean(node* &table)
{

    node* aux_table = nullptr;
    while (table != nullptr) 
    { 
        aux_table = table;
        table = table->prox;
        delete[] aux_table->name;
        delete aux_table;
    };
    delete table;
}


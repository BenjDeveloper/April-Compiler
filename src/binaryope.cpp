#include "../headers/binaryope.hpp"

namespace april
{
    Symbol* BinaryOpe::codeGen(CodeGenContext& context)
    {
        Symbol* value_left = left->codeGen(context);
        Symbol* value_right = right->codeGen(context);
        Symbol* tmp = new Symbol{};
        
        bool is_double = (value_left->type == Type::DOUBLE)?(true):((value_right->type == Type::DOUBLE)?(true):(false));
        tmp->type = (is_double)?(Type::DOUBLE):(Type::INTEGER);

        switch (ope)
        {
            case OPE::PLUS:
                if (is_double) { tmp->value._dval = ((value_left->type == Type::DOUBLE)?(value_left->value._dval):(value_left->value._ival)) + ((value_right->type == Type::DOUBLE)?(value_right->value._dval):(value_right->value._ival)); }
                else { tmp->value._ival = value_left->value._ival + value_right->value._ival; }
                break;
            
            case OPE::MIN:
                if (is_double) { tmp->value._dval = ((value_left->type == Type::DOUBLE)?(value_left->value._dval):(value_left->value._ival)) - ((value_right->type == Type::DOUBLE)?(value_right->value._dval):(value_right->value._ival)); }
                else { tmp->value._ival = value_left->value._ival - value_right->value._ival; }
                break;
            
            case OPE::MUL:
                if (is_double) { tmp->value._dval = ((value_left->type == Type::DOUBLE)?(value_left->value._dval):(value_left->value._ival)) * ((value_right->type == Type::DOUBLE)?(value_right->value._dval):(value_right->value._ival)); }
                else { tmp->value._ival = value_left->value._ival * value_right->value._ival; }
                break;
            
            case OPE::DIV:
                if (is_double) { tmp->value._dval = ((value_left->type == Type::DOUBLE)?(value_left->value._dval):(value_left->value._ival)) / ((value_right->type == Type::DOUBLE)?(value_right->value._dval):(value_right->value._ival)); }
                else { tmp->value._ival = value_left->value._ival / value_right->value._ival; }
                break;
        }

        return tmp;
    }
}
#include "../headers/binaryope.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* BinaryOpe::codeGen(CodeGenContext& context)
    {
        Symbol* value_left = left->codeGen(context);
        Symbol* value_right = right->codeGen(context);
        Symbol* tmp = new Symbol{};
       
        switch (ope)
        {
            case OPE::PLUS:
                tmp = *value_left + *value_right;
                break;
            
            case OPE::MIN:
                tmp = *value_left - *value_right;
                break;
            
            case OPE::MUL:
                tmp = *value_left * *value_right;
                break;
            
            case OPE::DIV:
                tmp = *value_left / *value_right;
                break;
            
            case OPE::AND:
                
                break;
            
            case OPE::OR:
                
                break;
        }
        return tmp;
    }
}
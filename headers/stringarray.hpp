#ifndef STRING_ARRAY_HPP
#define STRING_ARRAY_HPP

#include "identifier.hpp"
#include "expression.hpp"

namespace april
{
    class StringArray: public Expression
    {
        private:
            Identifier* ident_var;
            Expression* expr_indice;

        public: 
            StringArray(Identifier* ident_var, Expression* expr_indice): ident_var(ident_var), expr_indice(expr_indice){}
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //STRING_ARRAY_HPP
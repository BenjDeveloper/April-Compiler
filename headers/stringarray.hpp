#ifndef STRING_ARRAY_HPP
#define STRING_ARRAY_HPP

#include "identifier.hpp"
#include "expression.hpp"

namespace
{
    class StringArray: public Expression
    {
        private:
            Identifier* ident_var;
            int num;

        public: 
            StringArray(Identifier* ident_var, int num): ident_var(ident_var), num(num){}
            virtual Symbol* codeGen(CodeGenContext&);
    }; 
}

#endif //STRING_ARRAY_HPP
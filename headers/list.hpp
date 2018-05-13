#ifndef LIST_HPP
#define LIST_HPP

#include <vector>
#include "expression.hpp"

namespace april
{
    class List: public Expression
    {
        private:
            ExpressionList* expressions; 
            std::vector<Symbol*> elements;

        public:
            List(ExpressionList* expressions): expressions(expressions) {}
            ~List();
            virtual Symbol* codeGen(CodeGenContext&);
            Symbol* size();
            
    };
}

#endif //LIST_HPP
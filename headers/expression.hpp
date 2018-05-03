#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "node.hpp"

namespace april
{
    class Expression: public Node
    {
       public:
            virtual Symbol* codeGen(CodeGenContext&) = 0;
    };

}

#endif //EXPRESSION_HPP
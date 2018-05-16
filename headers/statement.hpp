#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "node.hpp"

namespace april
{
    class Statement: public Node
    {
        public:
            virtual ~Statement() {} 
            virtual Symbol* codeGen(CodeGenContext&) = 0;
    };
}

#endif //STATEMENT_HPP
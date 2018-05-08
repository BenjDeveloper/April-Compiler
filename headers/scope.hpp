#ifndef SCOPE_HPP
#define SCOPE_HPP

#include "statement.hpp"
#include "block.hpp"

namespace april
{
    class Scope: public Statement 
    {
        private:
            Block* block;
        public:
            Scope(Block* block):block(block) {}
            virtual Symbol* codeGen(CodeGenContext&); 
    };
}

#endif //SCOPE_HPP
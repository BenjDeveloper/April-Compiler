#ifndef CODE_GEN_CONTEXT_HPP
#define CODE_GEN_CONTEXT_HPP

#include "node.hpp"

namespace april
{
    class CodeGenContext
    {
        private:
            Block* current_block;  

        public:
            CodeGenContext();
            Symbol* runCode(Block*);
    };
}
#endif //CODE_GEN_CONTEXT_HPP 
#ifndef CODE_GEN_CONTEXT_HPP
#define CODE_GEN_CONTEXT_HPP
#include <string>
#include "block.hpp"

namespace april
{
    class CodeGenContext
    {
        private:
            Block* current_block;  
            int errors;
        public:
            CodeGenContext();
            Symbol* runCode(Block*);
            Block*& getCurrentBlock() { return current_block; }
            Symbol* findIdentLocals(std::string);
            Type typeOf(std::string);
            void addError() { ++errors; }
    };
}
#endif //CODE_GEN_CONTEXT_HPP
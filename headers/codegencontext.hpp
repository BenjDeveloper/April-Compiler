#ifndef CODE_GEN_CONTEXT_HPP
#define CODE_GEN_CONTEXT_HPP
#include <string>
#include <stack>
#include "block.hpp"

namespace april
{
    class CodeGenContext
    {
        private:
            Block* current_block;
            std::stack<Block*> stack_block;

            int errors;
        public:
            CodeGenContext();
            void runCode(Block*);
            Block*& getCurrentBlock() { return current_block; }
            Symbol*& findIdentLocals(std::string);
            Symbol* existIdenLocals(std::string);
            Type typeOf(std::string);
            void addError() { ++errors; }
            void push_block(Block*);
            void pop_block();
            void setCurrentBlock(Block*);
            std::stack<Block*>& getStackBlock() { return stack_block; }
    };
}
#endif //CODE_GEN_CONTEXT_HPP
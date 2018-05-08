#ifndef CODE_GEN_CONTEXT_HPP
#define CODE_GEN_CONTEXT_HPP
#include <string>
#include <stack>
#include <map>
#include "block.hpp"
#include "function.hpp"

namespace april
{
    using CallFunctionList = std::map<std::string, Function*>;
    
    enum class Scope
    {
        BLOCK,
        FUNCTION
    };

    class CodeGenContext
    {
        public:
            Scope scope_type;
            
        private:
            Block* current_block;
            std::stack<Block*> stack_block;
            int errors;
            CallFunctionList functions;
            Function* current_function;
           
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
            CallFunctionList& getFunctions() { return functions; }
            void addFunction(std::string name, Function* function) { functions[name] = function; }
            bool existFunction(std::string);
            bool deleteIdentLocals(std::string);
            void setCurrentFunction(Function* func) { current_function = func; }
            Function*& getCurrentFunction() { return current_function; }
    };
}
#endif //CODE_GEN_CONTEXT_HPP
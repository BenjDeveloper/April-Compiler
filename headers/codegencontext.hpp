#ifndef CODE_GEN_CONTEXT_HPP
#define CODE_GEN_CONTEXT_HPP

#include <string>
#include <stack>
#include <map>
#include "block.hpp"
#include "identifier.hpp"
#include "function.hpp"
#include "funclist.hpp"

namespace april
{
    using CallFunctionList = std::map<std::string, Function*>;
    using FunctionNameExternal = std::map<Type, std::vector<std::map<std::string, ExpressionList*>>>;

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
            std::vector<std::string> listMethods;
            Block* current_block;
            std::stack<Block*> stack_block;
            int errors;
            CallFunctionList functions;
            Function* current_function;
            FunctionNameExternal* function_external;

        public:
            CodeGenContext();
            void runCode(Block*);
            Block*& getCurrentBlock() { return current_block; }
            Symbol*& findIdentLocals(std::string);
            Symbol* existIdenLocals(std::string);
            Type typeOf(std::string);
            void addError() { ++errors; }
            std::vector<std::string> getMethods(){return listMethods;}
            bool findMethods(std::string);
            std::vector<std::string> loadMethod(std::string);
            void push_block(Block*);
            void pop_block();
            void setCurrentBlock(Block*);
            void popCurrentBlock();
            std::stack<Block*>& getStackBlock() { return stack_block; }
            CallFunctionList& getFunctions() { return functions; }
            void addFunction(std::string name, Function* function) { functions[name] = function; }
            bool existFunction(std::string);
            bool deleteIdentLocals(std::string);
            void setCurrentFunction(Function* func) { current_function = func; }
            Function*& getCurrentFunction() { return current_function; }
            void stopRootBlock();
            void stopBreakBlock();
            void printLocals();
            FunctionNameExternal*& getFunctionExternal() { return function_external; }

        private:
            void loadFunction();

    };
}
#endif //CODE_GEN_CONTEXT_HPP
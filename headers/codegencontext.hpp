#ifndef CODE_GEN_CONTEXT_HPP
#define CODE_GEN_CONTEXT_HPP
#include <string>
#include "block.hpp"
#include "identifier.hpp"

namespace april
{
    class CodeGenContext
    {
        private:
            Block* current_block;  
            int errors;            
            std::vector<std::string> listMethods;
            

        public:
            CodeGenContext();
            Symbol* runCode(Block*);
            Block*& getCurrentBlock() { return current_block; }
            Symbol* findIdentLocals(std::string);
            Type typeOf(std::string);
            void addError() { ++errors; }

            std::vector<std::string> getMethods(){return listMethods;}
            bool findMethods(std::string);
            std::vector<std::string> loadMethod(std::string);

    };
}
#endif //CODE_GEN_CONTEXT_HPP
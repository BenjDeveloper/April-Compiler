#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <vector>

namespace april
{
    class CodeGenContext;
    
    typedef struct STRUCINFO
    {
        int first_line;
        int last_line;
        std::string name_file;
    } STRUCINFO;

    enum class Type
    {
        integer,
        boolean,
        string,
        decimal,
        identifier,
        expression,
        variable,
        function
    };

    class Node
    {
        public:
            virtual ~Node() {}
            virtual llvm::Value* codeGen(CodeGenContext&) = 0;
            virtual Type getType() = 0;
            static void printError(std::string msg)
            {
                std::cerr << msg << std::endl;
            }
    };
}


#endif //NODE_HPP 
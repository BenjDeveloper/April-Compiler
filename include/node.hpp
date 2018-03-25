#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

namespace april
{
    class CodeGenContext;
    
    typedef struct STRUCINFO
    {
        int line;
        std::string file_name;
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
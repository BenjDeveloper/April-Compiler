#include <iostream>
#include "headers/block.hpp"
#include "headers/codegencontext.hpp"

extern int yyparse();
extern int yylex_destroy();
extern FILE* yyin;

extern april::Block* programBlock;

using namespace april;

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        std::cout << "Error: debe colocar la ruta de un fichero." << std::endl;
        return EXIT_FAILURE;
    }

    // std::string name_file = argv[1];
    std::string name_file = "test/test.april";

    yyin = fopen(name_file.c_str(), "r+");
    if (yyin == nullptr)
    {
        std::cout << "Error: no se pudo abrir el fichero." << std::endl;
        return EXIT_FAILURE;
    }

    yyparse();
    if (programBlock != nullptr)
    {
        // std::cout << ">> inicio main <<" << std::endl; 
        CodeGenContext contex;
        contex.runCode(programBlock);
        // std::cout << ">> final main <<" << std::endl; 
        
        if (programBlock != nullptr)
            delete programBlock;
    }
    
    if (yyin != nullptr)
        fclose(yyin);

    yylex_destroy();
    return 0;
}
#include <iostream>
#include "node.h"
#include "codegen.h"

extern int yyparse();
extern int yylex_destroy();
extern april::Block* programBlock;
extern FILE* yyin;

int main(int argc, char* argv[])
{
    std::string filename;

    if (argc > 1)
    {
        filename = "test_april/test_0.april";
    }

    yyin = fopen(filename.c_str(), "r+");
    if (yyin == nullptr)
    {
        std::cout << "Error al abrir el archivo: " << filename << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::cout << "*******************Inicio frontend*******************" << std::endl;
        yyparse();
        std::cout << "**********************FIN frontend*******************" << std::endl;
        april::CodeGenContext context;
        context.generateCode(*programBlock);
        context.runCode();
        if(yyin != nullptr) { fclose(yyin); }
        yylex_destroy();
    }

    return 0;
}
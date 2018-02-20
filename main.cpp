#include <iostream>
#include "include/codegencontext.hpp"

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
        std::cout << "Inicio del analisis del frontend listo :) " << std::endl;
        yyparse();
        std::cout << "Fin del analisis del frontend listo :) " << std::endl;
        april::CodeGenContext context;
        context.generateCode(*programBlock);
        context.runCode();
        if(yyin != nullptr) { fclose(yyin); }
        yylex_destroy();
    	delete programBlock;
	}

    return 0;
}

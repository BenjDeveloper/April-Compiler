#include <iostream>
#include "include/codegencontext.hpp"

extern int yyparse();
extern int yylex_destroy();
extern april::Block* programBlock;
extern FILE* yyin;
extern april::STRUCINFO* april_errors;


int main(int argc, char* argv[])
{
    std::string filename;
	
    if (argc > 1)
    {
        april_errors->file_name = "../../test_april/test_0.april";
    }

    yyin = fopen(april_errors->file_name.c_str(), "r+");
    if (yyin == nullptr)
    {
        std::cout << "Error al abrir el fichero: " << april_errors->file_name << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        if (yyparse())
        {
            return 1;
        }
        april::CodeGenContext context;
        if (context.generateCode(*programBlock))
        {
            context.runCode();
        }
        if(yyin != nullptr) { fclose(yyin); }
        yylex_destroy();
    	delete programBlock;
	}

    return 0;
}

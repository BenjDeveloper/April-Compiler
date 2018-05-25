#include <iostream>
#include <regex>
#include "headers/block.hpp"
#include "headers/codegencontext.hpp"

extern int yyparse();
extern int yylex_destroy();
extern FILE* yyin;
extern std::stack<std::string> file_names;
extern april::STRUCINFO* april_errors;

extern april::Block* programBlock;

using namespace april;

void usage();
int MAYOR_VERSION = 1;
int MENOR_VERSION = 0;
int MICRO_VERSION = 0;
bool RUN_MODE = false;
bool VERSION_MODE = false;
bool VERBOSE_MODE = false;
bool DEBUG_MODE = false;
bool ERROR_MODE = false;
std::string SYSTEM = "windows/amd64";

int main(int argc, char* argv[])
{
    std::string filename;

    if (argc > 1)
    {
		std::string command = argv[1];
		
		if (command == "run")
		{
			if (argc == 3 || argc == 4)
			{
				april_errors->file_name = argv[2];	
				std::regex re("[_a-zA-Z0-9\\./]*\\.april");
				//std::cout << "namefile: " << april_errors->file_name << std::endl;
				if (std::regex_match(april_errors->file_name, re))
				{
					RUN_MODE = true;
					if (argc == 4)
					{
						std::string arguments = argv[3];
						std::regex r("-[dv]+");
						if (std::regex_match(arguments, r))
						{
							if (arguments[1] == 'v')
								VERBOSE_MODE = true;
							else if (arguments[1] == 'd')
								DEBUG_MODE = true;

							if (arguments.size() == 3 && arguments[2] == 'v')
								VERBOSE_MODE = true;
							else if (arguments.size() == 3 && arguments[2] == 'd')
								DEBUG_MODE = true;
						}
						else
							ERROR_MODE = true;
					}
				}	
				else
					ERROR_MODE = true;
			}
			else
				ERROR_MODE = true;
		}
		else if (command == "version")
			VERSION_MODE = true;
		else
			ERROR_MODE = true;
    }
	else
		ERROR_MODE = true;
    
    if (ERROR_MODE)
	{
		usage();
		return EXIT_FAILURE;
	}
    else if (VERSION_MODE)
		std::cout << "April version " << MAYOR_VERSION << "." << MENOR_VERSION << "." << MICRO_VERSION << " " << SYSTEM << "\n"<< std::endl;
	
    else if (RUN_MODE)
    {
        //std::string name_file = argv[1];
        // std::string name_file = "test/test.april";

        yyin = fopen(april_errors->file_name.c_str(), "r+");
        if (yyin == nullptr)
        {
			std::cout << "Error: no se pudo encontrar el fichero: " << april_errors->file_name << "\n"<< std::endl;
            return EXIT_FAILURE;
        }
        
        file_names.push("");
        file_names.push(april_errors->file_name);

        if (yyparse())
        {
            yylex_destroy();
            return 1;
        }

        if (programBlock != nullptr)
        {
            CodeGenContext* context = new CodeGenContext{};
            bool result = context->runCode(programBlock);
            if (result)
                std::cout << "Compilacion con errores\n" << std::endl;

            if (programBlock != nullptr)
                delete programBlock;

            if (context != nullptr)
                delete context;
        }
        
        if (yyin != nullptr)
            fclose(yyin);

        yylex_destroy();
    }
    
    return 0;
}

void usage()
{
	std::cout << "Language April\n" << std::endl;
	std::cout << "Usage:" << std::endl;
	std::cout << "\t april command [arguments]\n" << std::endl;
	std::cout << "The commands are:" << std::endl;
	std::cout << "\t run\t\t compile and run April program" << std::endl;
	std::cout << "\t version\t print April version" << std::endl;

	std::cout << "\nThe arguments are:\n" << std::endl;
	std::cout << "\t -d \t\t active mode debug" << std::endl;
	std::cout << "\t -v \t\t view code generated" << std::endl;

	std::cout << "\n" << std::endl;
}
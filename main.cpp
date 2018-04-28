#include <iostream>
#include "include/codegencontext.hpp"
#include <regex>

extern int yyparse();
extern int yylex_destroy();
extern april::Block* programBlock;
extern FILE* yyin;
extern april::STRUCINFO* april_errors;

// april run namefile.april
// april run namefile.april -d
//april run namefile.april -dv

int MAYOR_VERSION = 1;
int MENOR_VERSION = 0;
int MICRO_VERSION = 0;
std::string SYSTEM = "windows/amd64";

bool RUN_MODE = false;
bool VERSION_MODE = false;
bool VERBOSE_MODE = false;
bool DEBUG_MODE = false;
bool ERROR_MODE = false;

void usage();

int main(int argc, char* argv[])
{
    std::string filename;

    if (argc > 1)
    {
		std::string command = argv[1];
		
		if (command == "run")
		{
			std::cout << "num: " << argc << std::endl;
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
		yyin = fopen(april_errors->file_name.c_str(), "r+");
		if (yyin == nullptr)
		{
			std::cout << "Error al abrir el fichero: " << april_errors->file_name << std::endl;
			return EXIT_FAILURE;
		}
		else
		{
			if (yyparse())
				return 1;

			april::CodeGenContext context;
			if (context.generateCode(*programBlock))
			{
				context.runCode();
			}
			if (yyin != nullptr) { fclose(yyin); }
			yylex_destroy();
			delete programBlock;
		}
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
#include <iostream>

extern int yyparse();

int main(){

	yyparse();
    return 0;
}

void yyerror(const char *msg)
{
    std::cout << "Error: " << msg << std::endl;
};
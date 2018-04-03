#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "../include/nativefn.hpp"
#include <regex>

extern "C" DECLSPEC void saludos()
{
	std::cout << "Hola, April!" << std::endl;
}

extern "C" DECLSPEC void print(char* str, ...)
{
    va_list args;
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
}

extern "C" DECLSPEC void println(char* str, ...)
{
    char* aux_str;
    va_list args;
    va_start(args, str);
    aux_str = (char*) malloc(strlen(str)+2);
    strcpy(aux_str, str);
    strcat(aux_str, "\n");
    vprintf(aux_str, args);
    va_end(args);
}

extern "C" DECLSPEC int str_compare(char* str0)
{
	std::string s0 = str0;
	std::vector<std::string>* v = s_plit(s0, ',');
	 
	if (v->size() == 2 && v->front() == v->back())
	{
		return 1;
	}
	
	delete v;
	return 0;
}

extern "C" DECLSPEC std::vector<std::string>* s_plit(std::string str, char token)
{
	std::vector<std::string>* result = new std::vector<std::string>();
	//std::regex re("_?[a-z]*");
	std::string chain;

	for (char& c: str)
	{
		if (c != token && c != ' ' && c != '"')
		{
			chain += c;
		}
		else if (c == token)
		{
			result->push_back(chain);
			chain = "";
		}
	}
	result->push_back(chain);
	return result;
}

extern "C" DECLSPEC char* str_concat(char* str0, char* str1)
{

	char* temp = new char( std::strlen(str0) + ::strlen(str1) +2);
	std::strcpy(temp, str0);
	std::strcat(temp, str1);
	std::vector<std::string>* vtemp = s_clean(temp);
	std::string t = vtemp->front();

	std::strcpy(temp, t.c_str());

	return temp;
}

extern "C" DECLSPEC std::vector<std::string>* s_clean(std::string str)
{
	std::vector<std::string>* result = new std::vector<std::string>();
	//std::regex re("_?[a-z]*");
	std::string chain;

	for (char& c : str)
	{
		if (c != '"')
		{
			chain += c;
		}
	}
	result->push_back(chain);
	return result;
}
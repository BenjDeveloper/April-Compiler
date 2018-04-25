#include <stdarg.h>
#include <stdio.h>
#include <iostream>	
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <regex>
#include <time.h>
#include "../include/nativefn.hpp"

//-----------------------------------------------------------------------------------
//                                      LIB IN-OUT                                   
//-----------------------------------------------------------------------------------
extern "C" DECLSPEC void _print(char* str, ...)
{
	//std::cout << str << std::endl;
    va_list args;
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
}

extern "C" DECLSPEC void _println(char* str, ...)
{
	//std::cout << str << std::endl;
    char* aux_str;
    va_list args;
    va_start(args, str);
    aux_str = (char*) malloc(strlen(str)+2);
    strcpy(aux_str, str);
    strcat(aux_str, "\n");	
    vprintf(aux_str, args);
    va_end(args);
}

extern "C" DECLSPEC void _iprintln(char* msn, int value)
{
	std::cout << msn <<" "<< value << std::endl;
}

extern "C" DECLSPEC void _iprintln2(int value)
{
	std::cout << value << std::endl;
}

extern "C" DECLSPEC void _dprintln(char* msn, double value)
{
	std::cout << msn << " " << value << std::endl;
}

extern "C" DECLSPEC void _dprintln2(double value)
{
	std::cout << value << std::endl;
}

extern "C" DECLSPEC void _sprintln(char* msn)
{
	std::cout << msn << std::endl;
}

extern "C" DECLSPEC void _sprint(char* msn)
{
	std::cout << msn ;
}

extern "C" DECLSPEC	char* _input()
{
	std::string input;
	_sprint("> ");
	std::getline(std::cin, input);
	char* result = new char(input.length() + 2);
	std::strcpy(result, input.c_str());
	return result;
}

//-----------------------------------------------------------------------------------
//                                      LIB UTIL-STRING                                 
//-----------------------------------------------------------------------------------
extern "C" DECLSPEC std::vector<std::string>* s_plit(std::string str, char token)
{
	std::vector<std::string>* result = new std::vector<std::string>();
	//std::regex re("_?[a-z]*");
	std::string chain;

	for (char& c : str)
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

extern "C" DECLSPEC char* s_clean(std::string str)
{
	std::vector<std::string>* Vresult = new std::vector<std::string>();
	std::string chain;

	for (char& c : str)
	{
		if (c != '"')
		{
			chain += c;
		}
	}
	Vresult->push_back(chain);
	std::string t = Vresult->front();
	char* result = new char(t.length() + 2);
	std::strcpy(result, t.c_str());
	return result;
}

extern "C" DECLSPEC bool _isNumber(std::string str)
{
	std::regex re("[0-9]+(\\.[0-9]+)?");

	if (regex_match(str, re))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------------
//                                      LIB STRING                                 
//-----------------------------------------------------------------------------------
extern "C" DECLSPEC int _strcompare(char* str0, char* str1)
{
	int result = std::strcmp(str0, str1);
	return result;
}

extern "C" DECLSPEC char* _strconcat(char* str0, char* str1)
{
	char* temp = new char(std::strlen(str0) + ::strlen(str1) + 2);
	std::strcpy(temp, str0);
	std::strcat(temp, str1);
	return temp;
}

extern "C" DECLSPEC int _strlength(char* str)
{
	return std::strlen(str);
}

extern "C" DECLSPEC char* _strcopy(char* str0, char* str1)
{
	char* temp1 = new char(std::strlen(str1) + 2);
	std::strcpy(temp1, str1);
	str0 = temp1;
	return str0;
}

//-----------------------------------------------------------------------------------
//                                      LIB CONST                                   
//-----------------------------------------------------------------------------------
extern "C" DECLSPEC const double pi = 3.14159265358979323846;

extern "C" DECLSPEC const double e = 2.71828182845904523536;

extern "C" DECLSPEC double _pi()
{
	return pi;
}

extern "C" DECLSPEC double _e()
{
	return e;
}

//-----------------------------------------------------------------------------------
//                                      LIB CAST                                   
//-----------------------------------------------------------------------------------
//extern "C" DECLSPEC int d_int(double){}

extern "C" DECLSPEC double _sdou(char* ent)
{
	std::string str = ent;
	if (_isNumber(str))
	{
		double d = double(std::atof(ent));
		return d;
	}
	else
	{
		_sprintln("tipos de datos incompatibles con DOUBLE"); // error saenz
		return 0;
	}
}

extern "C" DECLSPEC int _sint(char* ent)
{
	std::string str = ent;
	if (_isNumber(str))
	{ 
		int i = int(std::atoi(ent));
		return i;
	}
	else
	{
		_sprintln("tipos de datos incompatibles con INT"); // error saenz
		return 0;
	}
}

extern "C" DECLSPEC char* _dstr(double ent)
{
	std::string str = std::to_string(ent);
	char* result = new char(str.length()+2); 
	std::strcpy(result, str.c_str());
	return result;
}

extern "C" DECLSPEC char* _istr(int ent)
{
	std::string str = std::to_string(ent);
	char* result = new char(str.length() + 2);
	std::strcpy(result, str.c_str());
	return result;
}

//-----------------------------------------------------------------------------------
//                                      LIB MATH                                   
//-----------------------------------------------------------------------------------
extern "C" DECLSPEC int _imod(int a, int b)
{
	return int(a % b);
}

extern "C" DECLSPEC double _dmod(double a, double b)
{
	return (int)a % (int)b;
}

extern "C" DECLSPEC double _sqrt(double a)
{
	return std::sqrt(a);
}

extern "C" DECLSPEC double _sin(double a)
{
	return std::sin(a);
}

extern "C" DECLSPEC double _cos(double a)
{
	return std::cos(a);
}

extern "C" DECLSPEC double _tan(double a)
{
	return std::tan(a);
}

extern "C" DECLSPEC double _log(double a)
{
	return std::log(a);
}

extern "C" DECLSPEC int _irand(int inicio, int fin)
{
	std::srand(std::time(NULL));
	int margen = fin - inicio;
	int comienzo = inicio;
	if (inicio > fin) 
	{
		comienzo = fin;
		margen = margen * -1;
	}
	margen++;
	return  comienzo + (rand() % margen);
}

extern "C" DECLSPEC int _abs(int a)
{
	return std::abs(a);
}

extern "C" DECLSPEC double _pow(double a, double b)
{
	return std::pow(a, b);
}

//-----------------------------------------------------------------------------------
//                                      LIB HANDLE FILE                                   
//-----------------------------------------------------------------------------------

//#include <fstream>
//
//std::fstream 
//
//void franklin()
//{
//	std::fstream myfile("test.txt",std::ios::in,std::ios::app);
//	  
//
//	myfile.write("hola file", 100);
//}

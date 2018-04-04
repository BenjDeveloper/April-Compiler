//#if defined(_MSC_VER)
//#define DECLSPEC __declspec(dllexport) 
//#else
//#define DECLSPEC 
//#endif

#ifndef DECLSPEC
#define DECLSPEC __declspec(dllexport) 
#else
#define DECLSPEC  __declspec(dllimport) 
#endif


extern "C" DECLSPEC void saludos();
extern "C" DECLSPEC void print(char* str, ...);
extern "C" DECLSPEC void println(char* str, ...);

extern "C" DECLSPEC int str_compare(char*);
extern "C" DECLSPEC std::vector<std::string>* s_plit(std::string str, char token);
extern "C" DECLSPEC char* str_concat(char* str0, char* str1);
extern "C" DECLSPEC char* s_clean(std::string str);


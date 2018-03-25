//#if defined(_MSC_VER)
//#define DECLSPEC __declspec(dllexport) 
//#else
//#define DECLSPEC 
//#endif

#ifndef DECLSPEC
#define DECLSPEC __declspec(dllexport) 
#else
#define DECLSPEC __declspec(dllimport) 
#endif

extern "C" DECLSPEC void saludos();
extern "C" DECLSPEC void print(char* str, ...);
extern "C" DECLSPEC void println(char* str, ...);

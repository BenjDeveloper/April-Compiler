#ifndef DECLSPEC
#define DECLSPEC __declspec(dllexport) 
#else
#define DECLSPEC  __declspec(dllimport) 
#endif

//lib In-Out
extern "C" DECLSPEC void _println(char* str, ...);
extern "C" DECLSPEC void _sprintln(char*);
extern "C" DECLSPEC void _iprintln(char*, int);
extern "C" DECLSPEC void _iprintln2(int);
extern "C" DECLSPEC void _dprintln(char*, double);
extern "C" DECLSPEC void _dprintln2(double);
extern "C" DECLSPEC void _sprint(char*);
extern "C" DECLSPEC char* _input();

//lib util-String
extern "C" DECLSPEC std::vector<std::string>* s_plit(std::string, char);
extern "C" DECLSPEC char* s_clean(std::string);
extern "C" DECLSPEC bool _isNumber(std::string);

//lib string
extern "C" DECLSPEC int _strcompare(char*, char*);
extern "C" DECLSPEC char* _strconcat(char*, char*);
extern "C" DECLSPEC int _strlength(char*);
extern "C" DECLSPEC char* _strcopy(char*, char*);

//lib const
extern "C" DECLSPEC const double pi;
extern "C" DECLSPEC const double e;
extern "C" DECLSPEC double _pi();
extern "C" DECLSPEC double _e();

//lib cast
extern "C" DECLSPEC char* _dstr(double);
extern "C" DECLSPEC char* _istr(int);
extern "C" DECLSPEC int _sint(char*);
extern "C" DECLSPEC double _sdou(char*);
extern "C" DECLSPEC int _dint(double);


// lib match
extern "C" DECLSPEC int _imod(int, int);
extern "C" DECLSPEC double _dmod(double, double);
extern "C" DECLSPEC double _sqrt(double);
extern "C" DECLSPEC double _sin(double);
extern "C" DECLSPEC double _cos(double);
extern "C" DECLSPEC double _tan(double);
extern "C" DECLSPEC double _log(double);
extern "C" DECLSPEC int _irand(int, int);
extern "C" DECLSPEC int _abs(int);
extern "C" DECLSPEC double _pow(double, double);

// lib Handle Files
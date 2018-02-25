#include <iostream>
#include <cstring>

int main() 
{
    std::string* p = new std::string("hola");
    char* f = new char(std::strlen(p->c_str())+2);
    std::strcpy(f, (const char*)"-");
    std::strcat(f, p->c_str());
    std::cout << f << std::endl;
    
    delete p;
    delete f;
    return 0;
}
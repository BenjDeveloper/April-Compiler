// **********************************************************
// **                                                     ***
// **    Programado por Pandicorn & Kenshin Urashima      ***
// **    Test: raiz cuadrada de Newton                    ***
// **    command: >$ g++ test.cpp -o prueba && ./prueba   ***
// **    result: 1.41421                                  *** 
// **********************************************************

#include <iostream>
#include <vector>

double sqrt(double x)
{
    double z = 1.0;
    int cont = 0;

    while (cont < 10)
    {
        z = z-(((z*z)-x)/(2*z));
        cont++;
    }

    return z;
}

int main() 
{
    std::cout << "result: " << sqrt(2) << std::endl;

    return 0;
}
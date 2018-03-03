#include <iostream>
#include <vector>

int main() 
{
    std::vector<std::string> v;

    v.push_back("uno");
    v.push_back("dos");
    v.push_back("tres");
    std::vector<std::string>::iterator it;

    for (it = v.begin(); it != v.end(); it++)
    {
        std::cout << "it: "<< *it << std::endl;
    }

    // for (std::string& str : v)
    // {
    //     std::cout << str << std::endl;
    // }

    return 0;
}
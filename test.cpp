#include <iostream>
#include <map>


int main()
{
    std::map<std::string, int> m;

    m["uno"] = 1;
    m["dos"] = 2;
    m["cinco"] = 5;
    m["ocho"] = 8;

    std::map<std::string, int>::iterator it;
    
    for (it=m.begin(); it != m.end(); ++it)
    {
        std::cout << it->first << ", " << it->second << std::endl;
    }

    std::cout << m.find("ocho")->first << " => " << m.find("ocho")->second << std::endl;

    if (m.find("unos") == m.end() )
    {
        std::cout << "diez es nulo!" << std::endl;
    }

    std::cout << "uno--> " << m["sss"] << std::endl;

    return 0;
}
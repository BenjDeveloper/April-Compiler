#include "../headers/methodstruct.hpp"

namespace april
{
        MethodStruct::MethodStruct()
        {
            //metodos disponibles
            methods.push_back("len");
        }

        bool MethodStruct::find(std::string name)
        {
            for (std::string tmp: this->getMethods())
                if (name == tmp)
                {
                    return true;
                }

            return false;
        }

        void MethodStruct::call(std::string)
        {
            
        };
}

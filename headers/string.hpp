#ifndef STRING_HPP
#define STRING_HPP

#include <string>
#include "expression.hpp"

namespace april{

    class String: public Expression
    {
        private:
            std::string value;

        public:
            String(std::string);
            virtual Symbol* codeGen(CodeGenContext&);
            int len();
            std::string getValue(){return value;};
    };

}

#endif // STRING_HPP
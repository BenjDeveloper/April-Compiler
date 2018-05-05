#ifndef VALUE_HPP
#define VALUE_HPP

#include "integer.hpp"
#include "double.hpp"
#include "string.hpp"

namespace april
{
    class Value: public Integer, public Double, public String 
    {
        
        public:
            long long getValue(Integer*){return Integer::getValue();};
            double getValue(Double*){return Double::getValue();};
            std::string getValue(String*){return String::getValue();};
    };
}

#endif //VALUE_HPP
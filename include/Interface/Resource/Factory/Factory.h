
#ifndef Web_Service_Interface_Resource_Factory_INCLUDED
#define Web_Service_Interface_Resource_Factory_INCLUDED

#include <string>
#include "AbstractFactory.h"

namespace Interface
{
    namespace Resource
    {
        namespace Factory
        {

            class AbstractFactory;
            class Factory
            {
            public:
                static AbstractFactory *createResourceFactory(std::string &);

            private:
                Factory(){};
            };

        }
    }
}

#endif

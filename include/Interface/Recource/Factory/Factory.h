

#ifndef SmartHouse_Interface_Resource_Factory_Included
#define SmartHouse_Interface_Resource_Factory_Included

#include <string>
#include "IFactory.h"
namespace Interface
{
    namespace Resource
    {
        namespace Factory
        {

            class IFactory;
            class Factory
            {
            public:
                static IFactory *createResourceFactory(std::string &);

            private:
                Factory(){};
            };
       

        }
    }
}

#endif

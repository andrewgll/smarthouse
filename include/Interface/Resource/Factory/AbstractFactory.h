

#ifndef SmartHouse_Interface_Resource_Factory_Factory_Included
#define SmartHouse_Interface_Resource_Factory_Factory_Included

#include "Poco/Net/HTTPRequestHandler.h"

namespace Interface
{
    namespace Resource
    {
        namespace Factory
        {

            class AbstractFactory
            {
            public:
                 virtual Poco::Net::HTTPRequestHandler *createResource() = 0;
            };

        }
    }
}

#endif

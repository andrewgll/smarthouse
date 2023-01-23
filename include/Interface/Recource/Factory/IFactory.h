

#ifndef SmartHouse_Interface_Resource_Factory_IFactory_Included
#define SmartHouse_Interface_Resource_Factory_IFactory_Included

#include "Poco/Net/HTTPRequestHandler.h"

namespace Interface
{
    namespace Resource
    {
        namespace Factory
        {

            class IFactory
            {
            public:
                virtual Poco::Net::HTTPRequestHandler *createResource() = 0;
            };

        }
    }
}

#endif

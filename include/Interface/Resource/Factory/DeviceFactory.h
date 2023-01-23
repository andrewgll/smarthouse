

#ifndef Smart_House_Interface_Resource_Factory_Application_Factory_INCLUDED
#define Smart_House_Interface_Resource_Factory_Application_Factory_INCLUDED

#include "Factory.h"

namespace Interface
{
    namespace Resource
    {
        namespace Factory
        {

            class DeviceFactory : public AbstractFactory
            {
            public:
                Poco::Net::HTTPRequestHandler *createResource() override;
            };

        }
    }
}

#endif

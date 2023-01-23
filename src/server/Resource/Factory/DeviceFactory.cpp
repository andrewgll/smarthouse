#include "Interface/Resource/DeviceResource.h"
#include "Interface/Resource/Factory/DeviceFactory.h"

namespace Interface
{
    namespace Resource
    {
        namespace Factory
        {
            Poco::Net::HTTPRequestHandler *DeviceFactory::createResource()
            {
                return new DeviceResource();
            }
        }
    }
}

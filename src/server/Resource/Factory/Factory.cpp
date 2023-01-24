#include "Interface/Resource/Factory/Factory.h"
#include "Interface/Resource/Factory/DeviceFactory.h"

namespace Interface
{
    namespace Resource
    {
        namespace Factory
        {

            AbstractFactory *Factory::createResourceFactory(std::string &index)
            {
                // TODO: find better way to register routes

                AbstractFactory *factory = nullptr;
                if (index == "device")
                {
                    factory = new DeviceFactory();
                }

                return factory;
            }

        }
    }
}

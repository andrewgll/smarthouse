

#ifndef Smart_House_Interface_Resource_Application_INCLUDED
#define Smart_House_Interface_Resource_Application_INCLUDED

#include "AbstractResource.h"

namespace Interface
{
    namespace Resource
    {

        class DeviceResource : public AbstractResource
        {
        public:
            DeviceResource();

        protected:
            void handle_get(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;
            void handle_put(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;
            void handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;
        };

    }
}

#endif

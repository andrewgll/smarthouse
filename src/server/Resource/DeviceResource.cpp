#include "Interface/Resource/DeviceResource.h"

namespace Interface
{
    namespace Resource
    {

        DeviceResource::DeviceResource()
            : AbstractResource()
        {
        }

        void DeviceResource::handle_put(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
        {
            response.setContentType("application/vnd.api+json; charset=utf-8");
            response.send() << "Device Put Responce";
        }
        void DeviceResource::handle_get(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
        {
            response.setContentType("application/vnd.api+json; charset=utf-8");
            response.send() << "Device Get Responce";
        }

        void DeviceResource::handle_options(Poco::Net::HTTPServerRequest &,
                                            Poco::Net::HTTPServerResponse &response)
        {
            response.set("Allow", "GET, PUT, OPTIONS");
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.setContentType("text/plain; charset=utf-8");

            std::ostream &outputStream = response.send();
        }

    }
}

#include "Interface/Resource/ResourceNotFound.h"

namespace Interface
{
    namespace Resource
    {

        void ResourceNotFound::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
        {

            response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
            response.setReason(Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND);
            response.setContentType("application/vnd.api+json; charset=utf-8");
            response.send() << "ERROR: this route does not exist.";
        }

    }
}

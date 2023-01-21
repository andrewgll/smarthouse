#include "Ping.h"

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>

namespace handlers
{
void  Ping::handleRequest (
	Poco::Net::HTTPServerRequest& request,
	Poco::Net::HTTPServerResponse& response)
{

	response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
	response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");
	response.send() << "Pong!";
}

} 
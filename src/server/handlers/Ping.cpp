#include "Ping.h"
#include <iostream>

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>

namespace handlers
{
void  Ping::handleRequest (
	Poco::Net::HTTPServerRequest& request,
	Poco::Net::HTTPServerResponse& response)
{
	std::cout << "Client:" << request.clientAddress() << "\nServer:" << request.serverAddress() << '\n';
	
	response.send().flush();
	response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
}

} 
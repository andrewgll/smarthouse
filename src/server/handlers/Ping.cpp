#include "Ping.h"

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include "Poco/Util/ServerApplication.h"

using namespace Poco::Util;

namespace handlers
{
void  Ping::handleRequest (
	Poco::Net::HTTPServerRequest& request,
	Poco::Net::HTTPServerResponse& response)
{
	Application& app = Application::instance();
    app.logger().information("Ping request from %s", request.clientAddress().toString());
	
	response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
	response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");
	response.send()
		<< "<!DOCTYPE html>\n"
		<< "<html lang=\"en\">\n"
		<< "<head>\n<title>Server Page</title>\n</head>\n"
		<< "<body>\n<h2>Server sends hello!</h2>\n</body>\n"
		<< "</html>\n";
}

} 
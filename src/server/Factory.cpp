#include "Factory.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Util/ServerApplication.h>


#include "Ping.h"
#include "Devices.h"

using namespace Poco::Util;
using namespace Poco::Net;

namespace handlers
{

Poco::Net::HTTPRequestHandler* Factory::createRequestHandler(
	const Poco::Net::HTTPServerRequest& request)
{
	// log information about request
	Application& app = Application::instance();
    app.logger().information("%s %s request from %s",request.getMethod(),request.getURI(), request.clientAddress().toString());
	
	if (request.getMethod() != HTTPRequest::HTTP_GET)
		return nullptr;

	if (request.getURI() == "/ping")
		return new Ping();

	if(request.getURI() == "/devices")
		return new Devices();


	return nullptr;
}

} 
#include "Factory.h"

#include <iostream>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Util/ServerApplication.h>
#include "Poco/Logger.h"
#include <Poco/URI.h>

#include "Device.h"
#include "Devices.h"
#include "Ping.h"

using Poco::Logger;
using namespace Poco;
using namespace Poco::Util;
using namespace Poco::Net;

namespace handlers
{

Poco::Net::HTTPRequestHandler* Factory::createRequestHandler(
	const Poco::Net::HTTPServerRequest& request)
{
	// log information about request
	Logger& logger = Logger::get("SmartHouseLogger");
    logger.information("%s %s request from %s",request.getMethod(),request.getURI(), request.clientAddress().toString());
    try{    
		const URI uri = URI(request.getURI());

		// This is just testing of Poco functionality...

		// logger.information("URI: %s",uri.toString());
		// logger.information("Path: %s",uri.getPath());
		// logger.information("Host: %s",uri.getHost());
		// logger.information("Fragment: %s", uri.getFragment());
		// for(auto param : uri.getQueryParameters()){
		// 	logger.information("Query Param: %s %s", param.first, param.second);
		// }
		// logger.information("Scheme: %s",uri.getScheme());
		// logger.information("Query: %s", uri.getQuery());

		
		//TODO: figure out how to work with exceptions in Poco
		if(uri.empty())
			throw "No URI";
		if (uri.getPath() == "/ping")
			return new Ping();

		if(uri.getPath() == "/devices")
			return new Devices();

		if(uri.getPath() == "/device")
			return new Device();
    }
    catch (const Poco::Exception& exc)
    {
		// TODO figure out better way for loggin information(eg. in files...)
		logger.error(exc.displayText());
    }


	return nullptr;
}

} 
#include "Device.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <fstream>
#include <string>
#include <iterator>

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/FileStream.h>
#include <Poco/Path.h>

using namespace Poco;
using namespace Poco::Util;

namespace handlers
{
void Device::GetDevice(Poco::Net::HTTPServerRequest& request,
	Poco::Net::HTTPServerResponse& response, size_t id){
    
}
void Device::handleRequest (
	Poco::Net::HTTPServerRequest& request,
	Poco::Net::HTTPServerResponse& response)
{
    if(request.getMethod() == "GET"){
        GetDevice(request, response, 1);
    }
    else if(request.getMethod() == "POST"){

    }
}

} 
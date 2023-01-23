#include "Devices.h"

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
void Devices::GetDevices(Poco::Net::HTTPServerRequest& request,
	Poco::Net::HTTPServerResponse& response){
     Path path = Path();
    //TODO: create db
	char pathSeparator = Poco::Path::pathSeparator();
    if(pathSeparator == '\\'){
        path.assign("db\\devices.json");
    }
    else{
        path.assign("db/devices.json");
    }
    try{    
        response.setChunkedTransferEncoding(true);
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
        response.sendFile(path.toString(), "application/json");
    }
    catch (const Poco::Exception& exc)
    {
        std::cerr << exc.displayText() << std::endl;
    }
}
void Devices::handleRequest (
	Poco::Net::HTTPServerRequest& request,
	Poco::Net::HTTPServerResponse& response)
{
    if(request.getMethod() == "GET"){
        GetDevices(request, response);
    }
    else if(request.getMethod() == "POST"){

    }
}

} 
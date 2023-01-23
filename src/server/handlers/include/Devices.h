#include <Poco/Net/HTTPRequestHandler.h>
#ifndef SMARTHOUSE_HANDLER_DEVICES_H_
#define SMARTHOUSE_HANDLER_DEVICES_H_

namespace handlers
{

class Devices: public Poco::Net::HTTPRequestHandler
{
	
private:
	void handleRequest(
		Poco::Net::HTTPServerRequest& request,
		Poco::Net::HTTPServerResponse& response) override;
	void GetDevices(Poco::Net::HTTPServerRequest& request,
	Poco::Net::HTTPServerResponse& response);
	void PostDevices(Poco::Net::HTTPServerRequest& request,
	Poco::Net::HTTPServerResponse& response);
};
} 
#endif
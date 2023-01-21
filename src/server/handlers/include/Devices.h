#include <Poco/Net/HTTPRequestHandler.h>
#ifndef SMARTHOUSE_HANDLER_GETDEVICES_H_
#define SMARTHOUSE_HANDLER_GETDEVICES_H_

namespace handlers
{

class Devices: public Poco::Net::HTTPRequestHandler
{

private:
	void handleRequest(
		Poco::Net::HTTPServerRequest& request,
		Poco::Net::HTTPServerResponse& response) override;
};
} 
#endif
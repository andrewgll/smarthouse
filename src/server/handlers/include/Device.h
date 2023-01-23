#include <Poco/Net/HTTPRequestHandler.h>
#ifndef SMARTHOUSE_HANDLER_PING_H_
#define SMARTHOUSE_HANDLER_DEVICE_H_

namespace handlers
{

class Device: public Poco::Net::HTTPRequestHandler
{

private:
	void handleRequest(
		Poco::Net::HTTPServerRequest& request,
		Poco::Net::HTTPServerResponse& response) override;
    void GetDevice(
		Poco::Net::HTTPServerRequest& request,
		Poco::Net::HTTPServerResponse& response,
        size_t id
        );
    void PostDevice(
		Poco::Net::HTTPServerRequest& request,
		Poco::Net::HTTPServerResponse& response,
        size_t id
        );
};
} 
#endif
#ifndef SMARTHOUSE_FACTORY_H_
#define SMARTHOUSE_FACTORY_H_
#include <Poco/Net/HTTPRequestHandlerFactory.h>

namespace handlers
{

class Factory: public Poco::Net::HTTPRequestHandlerFactory
{
private:
	Poco::Net::HTTPRequestHandler* createRequestHandler(
		const Poco::Net::HTTPServerRequest& request) override;
};

} 
#endif
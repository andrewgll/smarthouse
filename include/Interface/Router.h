#ifndef SmartHouse_Interface_Router_Included
#define SmartHouse_Interface_Router_Included

#include <map>
#include <string>
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Resource/Factory/Factory.h"

namespace Interface
{

    class Router : public Poco::Net::HTTPRequestHandlerFactory
    {
    public:
        Router();

        void addRoute(const std::string &, const std::string&);
        Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request);

    private:
        void init();
        std::map<std::string, std::string> routingTable;
        Poco::Net::HTTPRequestHandler *getResource(const std::string &);
    };

}

#endif

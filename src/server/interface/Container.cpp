#include "Interface/Container.h"

#include <iostream>

#include "Poco/String.h"
#include "Poco/Net/HTTPServer.h"

namespace Interface {


    Container::Container()
        : port(9000),
          endpoint("localhost")
    { }

    Container::~Container()
    {
        delete router;
    }
    // Here application start
    int Container::main(const std::vector<std::string> &)
    {
        //create logger SmartHouseLogger for future using
		Poco::Logger& logger = Poco::Logger::get("SmartHouseLogger");
        auto * httpServerParams = new Poco::Net::HTTPServerParams();

        httpServerParams->setMaxQueued(250);
        httpServerParams->setMaxThreads(20);
        // register all routes and params
        Poco::Net::HTTPServer httpServer(getRouter(), Poco::Net::ServerSocket(Poco::UInt16(port)), httpServerParams);

        logger.information("SmartHouse server is started on %s:%i\ntype CRLT+C to finish it.",endpoint, port);

        httpServer.start();
        waitForTerminationRequest();
        httpServer.stop();

        logger.information("SmartHouse server stopped.");
        return Poco::Util::Application::EXIT_OK;

    }
    //accessors to private members...
    void Container::setPort(int _port)
    {
        port = _port;
    }
    
    void Container::setRouter(Poco::Net::HTTPRequestHandlerFactory * _router)
    {
        router = _router;
    }

    Poco::Net::HTTPRequestHandlerFactory * Container::getRouter()
    {
        return router;
    }


}

#include "Interface/Router.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Net/HTTPServerRequest.h"
#include <Poco/URI.h>
#include "Interface/Recource/ResourceNotFound.h"
#include "Interface/Recource/Factory/Factory.h"

using namespace Poco;
namespace Interface
{

    Router::Router()
    {
        init();
    }

    void Router::init()
    {
        // Register new routes here and corresponding handlers for them
        addRoute("/polls", "Interface::Resource::Factory::PollFactory");
        addRoute("/polls/votes", "Interface::Resource::Factory::PollVoteFactory");
        addRoute("/", "Interface::Resource::Factory::ApplicationFactory");
    }

    Poco::Net::HTTPRequestHandler *Router::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
    {
        return getResource(request.getURI());
    }

    Poco::Net::HTTPRequestHandler *Router::getResource(const std::string &route)
    {

        Poco::URI uri = Poco::URI(route);
        // extract path from url, eg.: localhost/device => /device
        // then search in routingTable for corresponding route
        auto factoryIndex = routingTable.find(uri.getPath());
        // if this routes aren't registered return not found
        if (factoryIndex == routingTable.end())
        {
            return new Interface::Resource::ResourceNotFound;
        }

        // create corresponding handler for uri
        // factoryIndex->second is uri eg. /device
        Interface::Resource::Factory::IFactory *factory =
            Interface::Resource::Factory::Factory::createResourceFactory(factoryIndex->second);
        return factory->createResource();
    }

    void Router::addRoute(const std::string &route, const std::string &factory)
    {
        routingTable[route] = factory;
    }

}

// TODO: learn about ApacheConnector
// COPIED: add support to Poco ApacheConnector
// POCO_BEGIN_MANIFEST(Poco::Net::HTTPRequestHandlerFactory)
// POCO_EXPORT_CLASS(Interface::Router)
// POCO_END_MANIFEST
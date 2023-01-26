#include "server/interface/router.h"

#include <Poco/URI.h>

#include "Poco/ClassLibrary.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "server/resource/factory/device_factory.h"
#include "server/resource/factory/factory.h"
#include "server/resource/resource_not_found.h"

using namespace Poco;
namespace interface {

Router::Router() { init(); }

void Router::init() {
  // Register new routes here and corresponding handlers for them
  addRoute("/device", "device");
}
Poco::Net::HTTPRequestHandler *Router::createRequestHandler(
    const Poco::Net::HTTPServerRequest &request) {
  return getResource(request.getURI());
}

Poco::Net::HTTPRequestHandler *Router::getResource(const std::string &route) {
  Poco::URI uri = Poco::URI(route);
  // extract path from url, eg.: localhost/device => /device
  // then search in routingTable for corresponding route
  auto factoryIndex = routingTable.find(uri.getPath());
  // if this routes aren't registered return not found
  if (factoryIndex == routingTable.end()) {
    return new interface::resource::ResourceNotFound;
  }

  // create corresponding handler for uri
  interface::resource::factory::AbstractFactory *factory =
      interface::resource::factory::Factory::createResourceFactory(
          factoryIndex->second);

  return factory->createResource();
}

void Router::addRoute(const std::string &route, const std::string &factory) {
  routingTable[route] = factory;
}

}  // namespace interface

// TODO: learn about ApacheConnector
// COPIED: add support to Poco ApacheConnector
// POCO_BEGIN_MANIFEST(Poco::Net::HTTPRequestHandlerFactory)
// POCO_EXPORT_CLASS(interface::Router)
// POCO_END_MANIFEST
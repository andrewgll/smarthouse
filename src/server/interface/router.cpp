#include "server/interface/router.h"

#include <string.h>

#include "Poco/ClassLibrary.h"
#include "Poco/Logger.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/URI.h"
#include "server/resource/factory/device_resource_factory.h"
#include "server/resource/resource_not_found.h"

using namespace Poco;
namespace interface {

Router::Router() { init(); }

void Router::init() {
  // Register new routes here and corresponding handlers for them
  addRoute("/device", new resource::DeviceResourceFactory());
}

Poco::Net::HTTPRequestHandler *Router::createRequestHandler(
    const Poco::Net::HTTPServerRequest &request) {
  Poco::URI uri = Poco::URI(request.getURI());
  // extract path from url, eg.: localhost/device => /device
  // then search in routingTable for corresponding route
  auto factoryIndex = routingTable.find(uri.getPath());
  // if this routes aren't registered return not found

  if (factoryIndex == routingTable.end()) {
    return new interface::resource::ResourceNotFound;
  }
  return factoryIndex->second->createResource();
}

}  // namespace interface

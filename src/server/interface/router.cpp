#include "server/interface/router.h"

#include <Poco/URI.h>

#include "Poco/ClassLibrary.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Logger.h"
#include "server/resource/abstract_resource.h"
#include "server/resource/device_resource.h"
#include "server/resource/resource_not_found.h"

using namespace Poco;
namespace interface {

Router::Router() { init(); }

void Router::init() {
  // Register new routes here and corresponding handlers for them
  addRoute<resource::DeviceResource>("/device");
}

Poco::Net::HTTPRequestHandler *Router::createRequestHandler(
    const Poco::Net::HTTPServerRequest &request) {
  Poco::Logger& logger = Poco::Logger::get("SmartHouseLogger");
  Poco::URI uri = Poco::URI(request.getURI());
  // extract path from url, eg.: localhost/device => /device
  // then search in routingTable for corresponding route
  auto factoryIndex = routingTable.find(uri.getPath());
  // if this routes aren't registered return not found
  
  if (factoryIndex == routingTable.end()) {
    return new interface::resource::ResourceNotFound;
  }
  return factoryIndex->second.get();
}

}  // namespace interface

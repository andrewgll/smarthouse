#ifndef SmartHouse_Interface_Router_Included
#define SmartHouse_Interface_Router_Included

#include <map>
#include <memory>
#include <string>

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "server/resource/factory/resource_factory.h"

namespace interface {

class Router : public Poco::Net::HTTPRequestHandlerFactory {
  using RoutingTableType =
      std::map<std::string, resource::ResourceFactory::Ptr>;

 public:
  Router();

  inline void addRoute(const std::string &path,
                       resource::ResourceFactory *resource_factory) {
    routingTable.insert(std::pair<std::string, resource::ResourceFactory::Ptr>(
        path, resource_factory));
  }

  Poco::Net::HTTPRequestHandler *createRequestHandler(
      const Poco::Net::HTTPServerRequest &request);

 private:
  void init();

  RoutingTableType routingTable;
};

}  // namespace interface

#endif

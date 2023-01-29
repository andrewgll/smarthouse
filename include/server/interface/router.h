#ifndef SmartHouse_Interface_Router_Included
#define SmartHouse_Interface_Router_Included

#include <map>
#include <string>

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "server/resource/abstract_resource.h"

namespace interface {

class Router : public Poco::Net::HTTPRequestHandlerFactory {
 public:
  Router();

  void addRoute(const std::string &, resource::AbstractResource* resource);
  Poco::Net::HTTPRequestHandler *createRequestHandler(
      const Poco::Net::HTTPServerRequest &request);

 private:
  void init();
   std::map<std::string, resource::AbstractResource*> routingTable;
};

}  // namespace interface

#endif

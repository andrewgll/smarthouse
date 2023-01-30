#ifndef SmartHouse_Interface_Router_Included
#define SmartHouse_Interface_Router_Included

#include <map>
#include <memory>
#include <string>

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "server/resource/abstract_resource.h"

namespace interface {

class Router : public Poco::Net::HTTPRequestHandlerFactory {
 public:
  Router();

  template <typename T>
  inline void addRoute(const std::string &path) {
    routingTable[path] = std::make_unique<T>();
  }

  Poco::Net::HTTPRequestHandler *createRequestHandler(
      const Poco::Net::HTTPServerRequest &request);

 private:
  void init();
  std::map<std::string, std::unique_ptr<resource::AbstractResource>>
      routingTable;
};

}  // namespace interface

#endif

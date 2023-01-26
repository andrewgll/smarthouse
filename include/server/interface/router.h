#ifndef SmartHouse_Interface_Router_Included
#define SmartHouse_Interface_Router_Included

#include <map>
#include <string>

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "server/resource/factory/factory.h"

namespace interface {

class Router : public Poco::Net::HTTPRequestHandlerFactory {
 public:
  Router();

  void addRoute(const std::string &, const std::string &);
  Poco::Net::HTTPRequestHandler *createRequestHandler(
      const Poco::Net::HTTPServerRequest &request);

 private:
  void init();
  std::map<std::string, std::string> routingTable;
  Poco::Net::HTTPRequestHandler *getResource(const std::string &);
};

}  // namespace interface

#endif

#ifndef SmartHouse_Container_Included
#define SmartHouse_Container_Included

#include <string>

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Util/ServerApplication.h"

namespace interface {

class Container : public Poco::Util::ServerApplication {
 public:
  Container();
  ~Container() override;

  void setPort(int);

  Poco::Net::HTTPRequestHandlerFactory *getRouter();
  void setRouter(Poco::Net::HTTPRequestHandlerFactory *);

 protected:
  int main(const std::vector<std::string> &args) override;

 private:
  int port;
  std::string endpoint;
  Poco::Net::HTTPRequestHandlerFactory *router;
};

}  // namespace interface

#endif

#ifndef SmartHouse_Container_Included
#define SmartHouse_Container_Included

#include <string>

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Util/ServerApplication.h"

namespace interface {

constexpr unsigned short HTTP_DEFAULT_PORT = 8080;

class Container : public Poco::Util::ServerApplication {
 public:
  Container();
  ~Container() override;

  void setPort(int);
  Poco::Net::HTTPRequestHandlerFactory *getRouter();
  void setRouter(Poco::Net::HTTPRequestHandlerFactory *);

 protected:
  void initLogger(const std::string &, const std::string &,
                  const std::string &);
  int main(const std::vector<std::string> &args) override;

 private:
  unsigned short port_;
  std::string endpoint_;
  Poco::Net::HTTPRequestHandlerFactory *router_;
};

}  // namespace interface

#endif

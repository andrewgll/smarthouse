#include "server/interface/container.h"

#include <iostream>

#include "Poco/Net/HTTPServer.h"
#include "Poco/String.h"
#include "server/interface/router.h"

namespace interface {

Container::Container()
    : port_(HTTP_DEFAULT_PORT), endpoint_("localhost"), router_(nullptr) {}

Container::~Container() { delete router_; }
// Here application start
int Container::main(const std::vector<std::string>&) {
  // create logger SmartHouseLogger for future using
  Poco::Logger& logger = Poco::Logger::get("SmartHouseLogger");
  auto* httpServerParams = new Poco::Net::HTTPServerParams();
  setRouter(new interface::Router());
  httpServerParams->setMaxQueued(250);
  httpServerParams->setMaxThreads(20);

  // register all routes and params

  auto router = getRouter();

  if (router == nullptr) {
    logger.fatal("No router set. Stopping server...");
    return Poco::Util::Application::EXIT_OK;
  }

  Poco::Net::HTTPServer httpServer(
      router, Poco::Net::ServerSocket(Poco::UInt16(port_)), httpServerParams);

  logger.information(
      "SmartHouse server is started on %s:%hu.\nType CTRL+C to stop it.",
      endpoint_, port_);

  httpServer.start();
  waitForTerminationRequest();
  httpServer.stop();
  httpServer.stopAll();

  logger.information("SmartHouse server stopped.");
  return Poco::Util::Application::EXIT_OK;
}
// accessors to private members...
void Container::setPort(int _port) { port_ = _port; }

void Container::setRouter(Poco::Net::HTTPRequestHandlerFactory* router) {
  router_ = router;
}

Poco::Net::HTTPRequestHandlerFactory* Container::getRouter() { return router_; }

}  // namespace interface

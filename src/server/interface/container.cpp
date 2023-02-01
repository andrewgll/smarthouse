#include "server/interface/container.h"

#include <iostream>

#include "Poco/AsyncChannel.h"
#include "Poco/AutoPtr.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Path.h"
#include "Poco/PatternFormatter.h"
#include "Poco/SplitterChannel.h"
#include "Poco/String.h"
#include "server/interface/router.h"

namespace interface {

Container::Container()
    : port_(HTTP_DEFAULT_PORT), endpoint_("localhost"), router_(nullptr) {}

Container::~Container() { delete router_; }
// Here application start
int Container::main(const std::vector<std::string>&) {
  // create logger SmartHouseLogger for future using
  initLogger();
  auto* httpServerParams = new Poco::Net::HTTPServerParams();
  setRouter(new interface::Router());
  httpServerParams->setMaxQueued(250);
  httpServerParams->setMaxThreads(20);

  // register all routes and params

  auto router = getRouter();

  if (router == nullptr) {
    logger().fatal("No router set. Stopping server...");
    return Poco::Util::Application::EXIT_OK;
  }

  Poco::Net::HTTPServer httpServer(
      router, Poco::Net::ServerSocket(Poco::UInt16(port_)), httpServerParams);

  logger().information("SmartHouse server is started on %s:%hu.", endpoint_,
                       port_);

  httpServer.start();
  waitForTerminationRequest();
  httpServer.stop();
  httpServer.stopAll();

  logger().information("SmartHouse server stopped.");
  return Poco::Util::Application::EXIT_OK;
}
// accessors to private members...
void Container::setPort(int _port) { port_ = _port; }

void Container::setRouter(Poco::Net::HTTPRequestHandlerFactory* router) {
  router_ = router;
}
void Container::initLogger() {
  // Create file channel with path to store log file
  Poco::AutoPtr<Poco::FileChannel> pFileChannel(new Poco::FileChannel);
  pFileChannel->setProperty("path", Poco::Path(Poco::Path::current())
                                        .append("logs")
                                        .append("logs.txt")
                                        .toString());
  // Archive if size >2K, creates new log file
  pFileChannel->setProperty("rotation", "3 K");
  // Naming for archived logs, e.g logs0.txt logs1.txt ...
  pFileChannel->setProperty("archive", "number");
  // Set maximum count of archived log files
  pFileChannel->setProperty("purgeCount", "3");
  // Add console channel
  Poco::AutoPtr<Poco::ConsoleChannel> pCons(new Poco::ConsoleChannel);
  // We need splitter to manage two channels
  Poco::AutoPtr<Poco::SplitterChannel> pSplitter(new Poco::SplitterChannel);

  pSplitter->addChannel(pCons);
  pSplitter->addChannel(pFileChannel);

  Poco::AutoPtr<Poco::PatternFormatter> pPF(new Poco::PatternFormatter);
  // Format log string

  // pPF->setProperty(
  //     "pattern",
  //     "{\"type\":\"%p\",\"time\":\"%Y-%m-%d %H:%M:%S\",\"data\":\"%t\"},");
  pPF->setProperty("pattern", "[%p] %Y-%m-%d %H:%M:%S %t");

  // this channel format log string
  Poco::AutoPtr<Poco::FormattingChannel> pFC(
      new Poco::FormattingChannel(pPF, pSplitter));

  // Create async channel, which will handle all other channels, starting from
  // formatting channel
  Poco::AutoPtr<Poco::AsyncChannel> pAsyncChannel(new Poco::AsyncChannel(pFC));

  setLogger(Poco::Logger::get("SmartHouseLogger"));
  logger().setChannel(pFC);
}
Poco::Net::HTTPRequestHandlerFactory* Container::getRouter() { return router_; }

}  // namespace interface

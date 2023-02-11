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
  initLogger("InfoLogger",
             Poco::Path(Poco::Path::current())
                 .append("logs")
                 .append("information.txt")
                 .toString(),
             "weekly");
  initLogger("ErrorLogger",
             Poco::Path(Poco::Path::current())
                 .append("logs")
                 .append("error.txt")
                 .toString(),
             "monthly");
  initLogger("WarningLogger",
             Poco::Path(Poco::Path::current())
                 .append("logs")
                 .append("warning.txt")
                 .toString(),
             "monthly");
  setLogger(Poco::Logger::get("InfoLogger"));
  auto* httpServerParams = new Poco::Net::HTTPServerParams();
  setRouter(new interface::Router());
  httpServerParams->setMaxQueued(250);
  httpServerParams->setMaxThreads(20);

  // register all routes and params

  auto router = getRouter();

  if (router == nullptr) {
    Poco::Logger::get("ErrorLogger").error("No router set. Stopping server...");
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
void Container::initLogger(const std::string& name, const std::string& filePath,
                           const std::string& rotation) {
  // Create file channel with path to store log file
  Poco::AutoPtr<Poco::FileChannel> pFileChannel(new Poco::FileChannel);
  pFileChannel->setProperty("path", Poco::Path(Poco::Path::current())
                                        .append("logs")
                                        .append("logs.txt")
                                        .toString());
  // Archive if logs older than 1 week, creates new log file
  pFileChannel->setProperty("rotation", "weekly");
  // Naming for archived logs, e.g logs0.txt logs1.txt ...
  pFileChannel->setProperty("archive", "number");
  // Set maximum count of archived log files
  pFileChannel->setProperty("purgeCount", "3");

  // Create file channel with custom path to store log file
  Poco::AutoPtr<Poco::FileChannel> pFileChannelBase(new Poco::FileChannel);
  pFileChannelBase->setProperty("path", filePath);
  // Archive if logs older than rotation, creates new log file
  pFileChannelBase->setProperty("rotation", rotation);
  pFileChannelBase->setProperty("archive", "number");
  pFileChannelBase->setProperty("purgeCount", "3");

  // Add console channel
  Poco::AutoPtr<Poco::ConsoleChannel> pCons(new Poco::ConsoleChannel);
  // We need splitter to manage three channels
  Poco::AutoPtr<Poco::SplitterChannel> pSplitter(new Poco::SplitterChannel);

  pSplitter->addChannel(pCons);
  pSplitter->addChannel(pFileChannel);
  pSplitter->addChannel(pFileChannelBase);

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
  Poco::Logger::get(name).setChannel(pAsyncChannel);
}
Poco::Net::HTTPRequestHandlerFactory* Container::getRouter() { return router_; }

}  // namespace interface

#ifndef SMARTHOUSE_INTERFACE_RESOURCE_LOGGER_RESOURCE_INCLUDED
#define SMARTHOUSE_INTERFACE_RESOURCE_LOGGER_RESOURCE_INCLUDED

#include "abstract_resource.h"

namespace interface {
namespace resource {

class LoggerResource : public AbstractResource {
 public:
  LoggerResource();

 protected:
  void handle_get(Poco::Net::HTTPServerRequest &,
                  Poco::Net::HTTPServerResponse &) override;
  void handle_options(Poco::Net::HTTPServerRequest &,
                      Poco::Net::HTTPServerResponse &) override;
};

}  // namespace resource
}  // namespace interface

#endif

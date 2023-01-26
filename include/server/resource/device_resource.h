#ifndef SmartHouse_Interface_Resource_Application_INCLUDED
#define SmartHouse_Interface_Resource_Application_INCLUDED

#include "abstract_resource.h"

namespace interface {
namespace resource {

class DeviceResource : public AbstractResource {
 public:
  DeviceResource();

 protected:
  void handle_get(Poco::Net::HTTPServerRequest &,
                  Poco::Net::HTTPServerResponse &) override;
  void handle_put(Poco::Net::HTTPServerRequest &,
                  Poco::Net::HTTPServerResponse &) override;
  void handle_options(Poco::Net::HTTPServerRequest &,
                      Poco::Net::HTTPServerResponse &) override;
};

}  // namespace resource
}  // namespace interface

#endif

#ifndef SmartHouse_Interface_Resource_Factory_Application_Factory_INCLUDED
#define SmartHouse_Interface_Resource_Factory_Application_Factory_INCLUDED

#include "factory.h"

namespace interface {
namespace resource {
namespace factory {

class DeviceFactory : public AbstractFactory {
 public:
  Poco::Net::HTTPRequestHandler *createResource() override;
};

}  // namespace factory
}  // namespace resource
}  // namespace interface

#endif

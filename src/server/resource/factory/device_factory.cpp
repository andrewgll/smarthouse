#include "server/resource/factory/device_factory.h"
#include "server/resource/device_resource.h"

namespace interface {
namespace resource {
namespace factory {
Poco::Net::HTTPRequestHandler *DeviceFactory::createResource() {
  return new DeviceResource();
}
}  // namespace factory
}  // namespace resource
}  // namespace interface

#include "server/resource/factory/factory.h"

#include "server/resource/abstract_resource.h"
#include "server/resource/device_resource.h"

namespace interface {
namespace resource {
namespace factory {

AbstractResource *Factory::createResource(std::string &index) {
  AbstractResource *resource = nullptr;
  if (index == "device") {
    resource = new DeviceResource();
  }

  return resource;
}

}  // namespace factory
}  // namespace resource
}  // namespace interface

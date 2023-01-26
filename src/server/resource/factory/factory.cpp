#include "server/resource/factory/factory.h"
#include "server/resource/factory/device_factory.h"

namespace interface {
namespace resource {
namespace factory {

AbstractFactory *Factory::createResourceFactory(std::string &index) {

  AbstractFactory *factory = nullptr;
  if (index == "device") {
    factory = new DeviceFactory();
  }

  return factory;
}

}  // namespace factory
}  // namespace resource
}  // namespace interface

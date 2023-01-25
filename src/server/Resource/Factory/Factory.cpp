#include "interface/resource/factory/factory.h"

#include "interface/resource/factory/device_factory.h"

namespace interface {
namespace resource {
namespace factory {

AbstractFactory *Factory::createResourceFactory(std::string &index) {
  // TODO: find better way to register routes

  AbstractFactory *factory = nullptr;
  if (index == "device") {
    factory = new DeviceFactory();
  }

  return factory;
}

}  // namespace factory
}  // namespace resource
}  // namespace interface

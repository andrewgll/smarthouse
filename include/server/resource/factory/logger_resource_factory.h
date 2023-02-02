#ifndef SMARTHOUSE_INTERFACE_RESOURCE_FACTORY_LOGGER_RESOURCE_FACTORY_INCLUDED
#define SMARTHOUSE_INTERFACE_RESOURCE_FACTORY_LOGGER_RESOURCE_FACTORY_INCLUDED

#include "resource_factory.h"
#include "server/resource/logger_resource.h"

namespace interface {
namespace resource {

class LoggerResourceFactory : public ResourceFactory {
 public:
  inline AbstractResource *createResource() override {
    return new LoggerResource();
  }
};

}  // namespace resource
}  // namespace interface

#endif  // SMARTHOUSE_INTERFACE_RESOURCE_FACTORY_DEVICE_RESOURCE_FACTORY_INCLUDED
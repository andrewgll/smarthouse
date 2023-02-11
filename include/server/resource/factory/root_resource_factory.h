#ifndef SMARTHOUSE_INTERFACE_RESOURCE_FACTORY_ROOT_RESOURCE_FACTORY_INCLUDED
#define SMARTHOUSE_INTERFACE_RESOURCE_FACTORY_ROOT_RESOURCE_FACTORY_INCLUDED

#include "resource_factory.h"
#include "server/resource/root_resource.h"

namespace interface {
namespace resource {

class RootResourceFactory : public ResourceFactory {
 public:
  inline AbstractResource *createResource() override {
    return new RootResource();
  }
};

}  // namespace resource
}  // namespace interface

#endif  // SMARTHOUSE_INTERFACE_RESOURCE_FACTORY_DEVICE_RESOURCE_FACTORY_INCLUDED
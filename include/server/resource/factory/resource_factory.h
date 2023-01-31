#ifndef SMARTHOUSE_INTERFACE_RESOURCE_FACTORY_RESOURCE_FACTORY_INCLUDED
#define SMARTHOUSE_INTERFACE_RESOURCE_FACTORY_RESOURCE_FACTORY_INCLUDED

#include <memory>

#include "server/resource/abstract_resource.h"

namespace interface {
namespace resource {

class ResourceFactory {
 public:
  using Ptr = std::unique_ptr<ResourceFactory>;
  virtual AbstractResource *createResource() = 0;
};

}  // namespace resource
}  // namespace interface

#endif  // SMARTHOUSE_INTERFACE_RESOURCE_FACTORY_RESOURCE_FACTORY_INCLUDED
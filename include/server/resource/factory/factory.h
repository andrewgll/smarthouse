#ifndef SmartHouse_Interface_Resource_Factory_INCLUDED
#define SmartHouse_Interface_Resource_Factory_INCLUDED

#include <string>

#include "abstract_factory.h"
#include "server/resource/abstract_resource.h"

namespace interface {
namespace resource {
namespace factory {

class Factory {
 public:
  static AbstractResource *createResource(std::string &);

 private:
  Factory(){};
};

}  // namespace factory
}  // namespace resource
}  // namespace interface

#endif

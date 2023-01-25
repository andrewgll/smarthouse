#ifndef Web_Service_Interface_Resource_Factory_INCLUDED
#define Web_Service_Interface_Resource_Factory_INCLUDED

#include <string>

#include "abstract_factory.h"

namespace interface {
namespace resource {
namespace factory {

class AbstractFactory;
class Factory {
 public:
  static AbstractFactory *createResourceFactory(std::string &);

 private:
  Factory(){};
};

}  // namespace factory
}  // namespace resource
}  // namespace interface

#endif

#ifndef SmartHouse_Interface_Resource_Factory_Factory_Included
#define SmartHouse_Interface_Resource_Factory_Factory_Included

#include "Poco/Net/HTTPRequestHandler.h"

namespace interface {
namespace resource {
namespace factory {

class AbstractFactory {
 public:
  virtual Poco::Net::HTTPRequestHandler *createResource() = 0;
};

}  // namespace factory
}  // namespace resource
}  // namespace interface

#endif

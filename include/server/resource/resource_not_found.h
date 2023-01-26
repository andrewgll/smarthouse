#ifndef SmartHouse_Interface_Resource_Resource_Not_Found_Included
#define SmartHouse_Interface_Resource_Resource_Not_Found_Included

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

namespace interface {
namespace resource {

class ResourceNotFound : public Poco::Net::HTTPRequestHandler {
 public:
  void handleRequest(Poco::Net::HTTPServerRequest &,
                     Poco::Net::HTTPServerResponse &);
};

}  // namespace resource
}  // namespace interface

#endif

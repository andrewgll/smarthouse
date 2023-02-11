#ifndef SMARTHOUSE_INTERFACE_RESOURCE_ROOT_RESOURCE_INCLUDED
#define SMARTHOUSE_INTERFACE_RESOURCE_ROOT_RESOURCE_INCLUDED

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "abstract_resource.h"

namespace interface {
namespace resource {

using namespace Poco::Net;

class RootResource : public AbstractResource {
 protected:
  void handle_get(Poco::Net::HTTPServerRequest &,
                  Poco::Net::HTTPServerResponse &);
  void handle_options(Poco::Net::HTTPServerRequest &,
                      Poco::Net::HTTPServerResponse &);
};

}  // namespace resource
}  // namespace interface

#endif

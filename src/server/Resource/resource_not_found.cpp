#include "interface/resource/resource_not_found.h"

namespace interface {
namespace resource {

void ResourceNotFound::handleRequest(Poco::Net::HTTPServerRequest &request,
                                     Poco::Net::HTTPServerResponse &response) {
  response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
  response.setReason(Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND);
  response.setContentType("application/vnd.api+json; charset=utf-8");
  response.send() << "ERROR: this route does not exist.";
}

}  // namespace resource
}  // namespace interface

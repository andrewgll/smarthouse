#include "server/resource/resource_not_found.h"

#include "server/resource/utils/exception.h"

namespace interface {
namespace resource {

void ResourceNotFound::handleRequest(HTTPServerRequest &request,
                                     HTTPServerResponse &response) {
  response.setStatus(HTTPResponse::HTTP_NOT_FOUND);
  response.setReason(HTTPResponse::HTTP_REASON_NOT_FOUND);
  response.setContentType("application/vnd.api+json; charset=utf-8");
  response.send() << "This route does not exist.";
  throw utils::HttpServerException(HTTPResponse::HTTP_REASON_BAD_REQUEST,
                                   "This route does not exist.",
                                   HTTPResponse::HTTP_BAD_REQUEST);
}

}  // namespace resource
}  // namespace interface

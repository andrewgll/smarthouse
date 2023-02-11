#include "server/resource/root_resource.h"

namespace interface {
namespace resource {

void RootResource::handle_get(HTTPServerRequest &request,
                              HTTPServerResponse &response) {
  response.setStatusAndReason(HTTPResponse::HTTP_OK);
  // TODO get version from gitlab CI
  response.send() << "SmartHouse server is working!\nversion: 1.2";
}
void RootResource::handle_options(Poco::Net::HTTPServerRequest &,
                                    Poco::Net::HTTPServerResponse &response) {
  response.set("Allow", "GET");
  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.setContentType("text/plain; charset=utf-8");
  response.send();
}
}  // namespace resource
}  // namespace interface

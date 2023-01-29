#include "server/resource/device_resource.h"

#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/Path.h"
#include "server/db/device_db_service.h"
#include "server/resource/utils/exception.h"
#include "server/resource/utils/json_error_builder.h"

namespace interface {
namespace resource {

DeviceResource::DeviceResource() : AbstractResource() {}

void DeviceResource::handle_put(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  std::string str(std::istreambuf_iterator<char>(request.stream()), {});
  Poco::JSON::Parser parser;
  dbService.updateDevice(parser.parse(str).extract<Poco::JSON::Object::Ptr>(),
                         getQueryParameter("id"));
  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.send();
}
void DeviceResource::handle_get(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  auto device = dbService.findDevice(getQueryParameter("id"));
  Poco::JSON::Stringifier::condense(device, response.send());
}

void DeviceResource::handle_post(Poco::Net::HTTPServerRequest &request,
                                 Poco::Net::HTTPServerResponse &response) {
  std::string str(std::istreambuf_iterator<char>(request.stream()), {});
  Poco::JSON::Parser parser;
  dbService.addDevice(parser.parse(str).extract<Poco::JSON::Object::Ptr>());
  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.send();
}
void DeviceResource::handle_delete(Poco::Net::HTTPServerRequest &request,
                                   Poco::Net::HTTPServerResponse &response) {
  dbService.deleteDevice(getQueryParameter("id"));
  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.send();
}
void DeviceResource::handle_options(Poco::Net::HTTPServerRequest &,
                                    Poco::Net::HTTPServerResponse &response) {
  response.set("Allow", "GET, POST, PUT, OPTIONS");
  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.setContentType("text/plain; charset=utf-8");
  response.send();
}

}  // namespace resource
}  // namespace interface

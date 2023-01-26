#include "server/resource/device_resource.h"

#include "Poco/Logger.h"
#include "Poco/Path.h"
#include "server/db/device_db_service.h"
#include "server/resource/utils/exception.h"

namespace interface {
namespace resource {

DeviceResource::DeviceResource() : AbstractResource() {}

void DeviceResource::handle_put(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {}
void DeviceResource::handle_get(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  try {
    Poco::Path path(Poco::Path::current());
    path.append("db").append("devices.json");
    db::DeviceDBService service(path);
    service.findDevice("1");
  } catch (resource::Exception &exception) {
    handleHttpStatusCode(exception.code(), response);
    std::ostream &outputStream = response.send();
    outputStream << toJson(exception);
  }

  response.send() << "Device Get Responce";
}

void DeviceResource::handle_options(Poco::Net::HTTPServerRequest &,
                                    Poco::Net::HTTPServerResponse &response) {
  response.set("Allow", "GET, PUT, OPTIONS");
  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.setContentType("text/plain; charset=utf-8");

  std::ostream &outputStream = response.send();
}

}  // namespace resource
}  // namespace interface

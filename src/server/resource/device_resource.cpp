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
  Poco::Logger &logger = Poco::Logger::get("SmartHouseLogger");
  try {
    Poco::Path path(Poco::Path::current());
    path.append("db").append("devices.json");
    db::DeviceDBService service(path);
    std::string id = getQueryParameter("id");
    response.send() << service.findDevice(id).toString();
  } catch (resource::Exception &exception) {
    logger.information("handle code");
    handleHttpStatusCode(exception.code(), response);
    response.send() << toJson(exception);
  }
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

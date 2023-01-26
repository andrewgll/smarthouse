#include "server/resource/device_resource.h"

#include "Poco/Logger.h"
#include "Poco/Path.h"
#include "server/db/device_db_service.h"
#include "server/resource/utils/exception.h"
#include "server/resource/utils/json_error_builder.h"

namespace interface {
namespace resource {

DeviceResource::DeviceResource() : AbstractResource() {}

void DeviceResource::handle_put(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {}
void DeviceResource::handle_get(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  Poco::Path path(Poco::Path::current());
  path.append("db").append("devices.json");
  db::DeviceDBService service(path);
  std::string id = getQueryParameter("id");
  std::string device = service.findDevice(id).toString();
  response.send() << device;
}

void DeviceResource::handle_post(Poco::Net::HTTPServerRequest &request,
                                 Poco::Net::HTTPServerResponse &response) {}
void DeviceResource::handle_delete(Poco::Net::HTTPServerRequest &request,
                                   Poco::Net::HTTPServerResponse &response) {}
void DeviceResource::handle_options(Poco::Net::HTTPServerRequest &,
                                    Poco::Net::HTTPServerResponse &response) {
  response.set("Allow", "GET, POST, PUT, OPTIONS");
  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.setContentType("text/plain; charset=utf-8");
  response.send();
}

}  // namespace resource
}  // namespace interface

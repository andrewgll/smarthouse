#include "server/resource/logger_resource.h"

#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/Path.h"
#include "server/db/device_db_service.h"
#include "server/resource/utils/exception.h"
#include "server/resource/utils/json_error_builder.h"

namespace interface {
namespace resource {

LoggerResource::LoggerResource() : AbstractResource() {}

void LoggerResource::handle_get(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  std::string id = getQueryParameter("id", false);
  if (id == "") {
    auto device = dbService.loadDB();
    Poco::JSON::Stringifier::condense(device, response.send());

  } else {
    auto device = dbService.findDevice(id);
    Poco::JSON::Stringifier::condense(device, response.send());
  }
}
void LoggerResource::handle_options(Poco::Net::HTTPServerRequest &,
                                    Poco::Net::HTTPServerResponse &response) {
  response.set("Allow", "GET, OPTIONS");
  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.setContentType("text/plain; charset=utf-8");
  response.send();
}
}  // namespace resource
}  // namespace interface

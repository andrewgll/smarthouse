#include "server/resource/device_resource.h"

#include <memory>

#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/Path.h"
#include "server/db/db_service.h"
#include "server/resource/utils/exception.h"
#include "server/resource/utils/json_error_builder.h"

namespace interface {
namespace resource {

using namespace Poco::Net;
DeviceResource::DeviceResource()
    : AbstractResource(Poco::Path(Poco::Path::current())
                           .append("db")
                           .append("devices.json")) {}
void DeviceResource::handle_smoke() {
  auto &logger = Poco::Logger::get("WarningLogger");
  logger.warning("Smoke detected!");
  auto data = Poco::SharedPtr<Poco::JSON::Object>(new Poco::JSON::Object());

  logger.warning("Opening windows.");
  data->set("status", "opened");
  dbService->update(data, {{"name", "window"}});

  logger.warning("Changing sensor status smokeNOTDetected.");
  data->set("status", "smokeNOTDetected");
  dbService->update(data, {{"name", "smokeSensor"}});

  logger.warning("Turning off oven.");
  data->set("status", "off");
  dbService->update(data, {{"name", "oven"}});
}
void DeviceResource::handle_flood() {
  auto &logger = Poco::Logger::get("WarningLogger");
  logger.warning("Flood detected!");
  auto data = Poco::SharedPtr<Poco::JSON::Object>(new Poco::JSON::Object());

  logger.warning("Closing all water in house.");
  data->set("status", "closed");
  dbService->update(data, {{"name", "tap"}});

  logger.warning("Turning off ligths.");
  data->set("status", "off");
  dbService->update(data, {{"name", "light"}});

  logger.warning("Turning off devices.");
  dbService->update(data, {{"name", "smartDevice"}});

  logger.warning("Changing sensor status to floodNOTDetected.");
  data->set("status", "floodNOTDetected");
  dbService->update(data, {{"name", "waterSensor"}});
}
void DeviceResource::handle_put(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  if (queryStringParameters.size() == 0) {
    throw utils::HttpServerException(HTTPResponse::HTTP_REASON_BAD_REQUEST,
                                     "Identificator is missing at URL.",
                                     HTTPResponse::HTTP_BAD_REQUEST);
  }
  Poco::JSON::Parser parser;
  auto data = parser.parse(request.stream()).extract<Poco::JSON::Object::Ptr>();
  dbService->update(data, queryStringParameters);
  std::string status = data->get("status");
  if (status == "smokeDetected") {
    handle_smoke();
  } else if (status == "floodDetected") {
    handle_flood();
  }
  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.send();
}
void DeviceResource::handle_get(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  auto item = dbService->find(queryStringParameters);
  response.setContentType("application/json");
  if (item->size() == 1) {
    Poco::JSON::Stringifier::condense(item->getObject(0), response.send());
  }
  Poco::JSON::Stringifier::condense(item, response.send());
}

void DeviceResource::handle_post(Poco::Net::HTTPServerRequest &request,
                                 Poco::Net::HTTPServerResponse &response) {
  Poco::JSON::Parser parser;
  dbService->add(
      parser.parse(request.stream()).extract<Poco::JSON::Object::Ptr>());
  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.send();
}
void DeviceResource::handle_delete(Poco::Net::HTTPServerRequest &request,
                                   Poco::Net::HTTPServerResponse &response) {
  if (queryStringParameters.size() == 0) {
    throw interface::resource::utils::HttpServerException(
        Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST, "Id not specified",
        Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
  }
  dbService->remove(queryStringParameters.front().second);
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

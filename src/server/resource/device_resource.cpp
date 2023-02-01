#include "server/resource/device_resource.h"

#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/Path.h"
#include "server/db/device_db_service.h"
#include "server/resource/utils/exception.h"
#include "server/resource/utils/json_error_builder.h"

namespace interface {
namespace resource {

using namespace Poco::Net;

DeviceResource::DeviceResource() : AbstractResource() {}

void DeviceResource::handle_put(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  if (queryStringParameters.size() == 0) {
    throw utils::HttpServerException(HTTPResponse::HTTP_REASON_BAD_REQUEST,
                                     "Attribute  is missing at URL.",
                                     HTTPResponse::HTTP_BAD_REQUEST);
  }
  for (auto it = queryStringParameters.begin();
       it != queryStringParameters.end(); it++) {
    if (it->first == "id") {
      std::string str(std::istreambuf_iterator<char>(request.stream()), {});
      Poco::JSON::Parser parser;
      dbService.updateDevice(
          parser.parse(str).extract<Poco::JSON::Object::Ptr>(),
          it->second);
    }
    if (it->first == "status") {
      auto device = dbService.findDevice(it->second);
      Poco::JSON::Stringifier::condense(device->getValue<std::string>("status"),
                                        response.send());
    }
  }

  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.send();
}
void DeviceResource::handle_get(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  if (queryStringParameters.size() == 0) {
    auto device = dbService.loadDB();
    Poco::JSON::Stringifier::condense(device, response.send());
  }
  for (auto it = queryStringParameters.begin();
       it != queryStringParameters.end(); it++) {
    if (it->first == "id") {
      auto device = dbService.findDevice(it->second);
      Poco::JSON::Stringifier::condense(device, response.send());
    }
    if (it->first == "status") {
      auto device = dbService.findDevice(it->second);
      Poco::JSON::Stringifier::condense(device->getValue<std::string>("status"),
                                        response.send());
    }
  }
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

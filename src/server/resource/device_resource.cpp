#include "server/resource/device_resource.h"

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

void DeviceResource::handle_put(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  if (queryStringParameters.size() == 0) {
    throw utils::HttpServerException(HTTPResponse::HTTP_REASON_BAD_REQUEST,
                                     "Identificator is missing at URL.",
                                     HTTPResponse::HTTP_BAD_REQUEST);
  }

  std::string str(std::istreambuf_iterator<char>(request.stream()), {});
  Poco::JSON::Parser parser;
  dbService->updateItem(parser.parse(str).extract<Poco::JSON::Object::Ptr>(),
                        queryStringParameters.front().second);

  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.send();
}
void DeviceResource::handle_get(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  if (queryStringParameters.size() == 0) {
    auto device = dbService->loadDB();
    Poco::JSON::Stringifier::condense(device, response.send());
  }
  for (auto it = queryStringParameters.begin();
       it != queryStringParameters.end(); it++) {
    auto device = dbService->findItem(it->second);
    if (it->first == "id") {
      Poco::JSON::Stringifier::condense(device, response.send());
    }
    if (it->first == "status") {
      Poco::JSON::Stringifier::condense(device->getValue<std::string>("status"),
                                        response.send());
    }
  }
}

void DeviceResource::handle_post(Poco::Net::HTTPServerRequest &request,
                                 Poco::Net::HTTPServerResponse &response) {
  std::string str(std::istreambuf_iterator<char>(request.stream()), {});
  Poco::JSON::Parser parser;
  dbService->addItem(parser.parse(str).extract<Poco::JSON::Object::Ptr>());
  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.send();
}
void DeviceResource::handle_delete(Poco::Net::HTTPServerRequest &request,
                                   Poco::Net::HTTPServerResponse &response) {
  dbService->deleteItem(getQueryParameter("id"));
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

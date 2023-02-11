#include "server/resource/logger_resource.h"

#include "Poco/FileStream.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/Path.h"
#include "server/db/db_service.h"
#include "server/resource/utils/exception.h"
#include "server/resource/utils/json_error_builder.h"

namespace interface {
namespace resource {

void LoggerResource::handle_get(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  Poco::FileInputStream fis;
  std::string name = "";
  if (queryStringParameters.empty()) {
    name = "logs.txt";
  } else if (queryStringParameters.front().first == "type") {
    name = queryStringParameters.front().second.append(".txt");
  } else {
    throw utils::HttpServerException(

        HTTPResponse::HTTP_REASON_BAD_REQUEST, "Invalid argument",
        HTTPResponse::HTTP_BAD_REQUEST);
  }
  try {
    fis.open(Poco::Path(Poco::Path::current())
                 .append("logs")
                 .append(name)
                 .toString(),
             std::ios::in);
  } catch (...) {
    throw utils::HttpServerException(HTTPResponse::HTTP_REASON_BAD_REQUEST,
                                     "Invalid logs name",
                                     HTTPResponse::HTTP_BAD_REQUEST);
  }
  std::istreambuf_iterator<char> eos;
  std::string str(std::istreambuf_iterator<char>(fis), eos);
  fis.close();
  response.send() << str;
  return;
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

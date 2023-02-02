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

LoggerResource::LoggerResource() : AbstractResource() {}

void LoggerResource::handle_get(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  Poco::FileInputStream fis(Poco::Path(Poco::Path::current())
                                .append("logs")
                                .append("logs.txt")
                                .toString());
  std::istreambuf_iterator<char> eos;
  std::string str(std::istreambuf_iterator<char>(fis), eos);
  fis.close();
  response.send() << str;
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

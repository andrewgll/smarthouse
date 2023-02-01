#include "server/resource/utils/exception.h"

#include "Poco/LogStream.h"
#include "Poco/Logger.h"
using Poco::Logger;
using Poco::LogStream;

namespace interface {
namespace resource {
namespace utils {
HttpServerException::HttpServerException(const std::string& type,
                                         const std::string& message,
                                         ResponseCode status_code)
    : status_code_(status_code), type_(type), message_(message) {
  Logger& logger = Logger::get("HttpServerException");
  LogStream lstr(logger);
  lstr << "Exception was created: "
       << "Type: " << type_ << ", Message: " << message_
       << ", Status code: " << status_code_ << std::endl;
}
}  // namespace utils
}  // namespace resource
}  // namespace interface
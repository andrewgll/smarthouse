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
  Poco::Logger::get("ErrorLogger")
      .error("Type: " + type_ + ", Message: " + message_ +
             " Status code: " + std::to_string(status_code_));
}
}  // namespace utils
}  // namespace resource
}  // namespace interface
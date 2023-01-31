
#ifndef SmartHouse_Interface_Resource_Exception_INCLUDED
#define SmartHouse_Interface_Resource_Exception_INCLUDED

#include <stdexcept>

#include "Poco/Net/HTTPResponse.h"

namespace interface {
namespace resource {

class A {
 public:
  enum B { a, b, c };
};

class HttpServerException : public std::exception {
  using ResponseCode = Poco::Net::HTTPResponse::HTTPStatus;

 public:
  HttpServerException(const std::string& type, const std::string& message,
                      ResponseCode status_code);

  inline ResponseCode code() const { return status_code_; }
  inline const std::string& type() const { return type_; }
  inline const std::string& message() const { return message_; }

 private:
  ResponseCode status_code_;
  std::string type_;
  std::string message_;
};

}  // namespace resource
}  // namespace interface

#endif

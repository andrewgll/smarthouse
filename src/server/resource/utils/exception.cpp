#include "server/resource/utils/exception.h"

namespace interface {
namespace resource {


    Exception::Exception(const std::string & type, const std::string & message, int statusCode)
        : _statusCode(statusCode),
          _type(type),
          _message(message)
    {}

    int Exception::code() const
    {
        return _statusCode;
    }

    std::string Exception::type() const
    {
        return _type;
    }

    std::string Exception::message() const
    {
        return _message;
    }


} }

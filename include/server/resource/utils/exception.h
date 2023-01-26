
#ifndef SmartHouse_Interface_Resource_Exception_INCLUDED
#define SmartHouse_Interface_Resource_Exception_INCLUDED

#include <stdexcept>

namespace interface {
namespace resource {


    class Exception : public std::exception
    {
    public:
        Exception(const std::string & type, const std::string & message, int statusCode);

        int code() const;
        std::string type() const;
        std::string message() const;

    private:
        int _statusCode;
        std::string _type;
        std::string _message;

    };


} }

#endif

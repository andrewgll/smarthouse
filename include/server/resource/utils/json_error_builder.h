
#ifndef SmartHouse_Interface_Handling_JSONAPI_Json_API_Error_Builder_INCLUDED
#define SmartHouse_Interface_Handling_JSONAPI_Json_API_Error_Builder_INCLUDED
#include <string>
#include "Poco/Dynamic/Struct.h"

namespace interface {
namespace handling {
    class JsonErrorBuilder
    {
    public:
        explicit JsonErrorBuilder(const std::string &);
        ~JsonErrorBuilder() = default;

        //
        Poco::DynamicStruct & build() ;

        void withStatusCode(int) ;
        void withType(const std::string &) ;
        void sourceAt(const std::string &) ;
        void withDetails(const std::string &) ;

    private:
        std::string host;
        Poco::DynamicStruct commonError;
        Poco::DynamicStruct rootJsonStructure;
        Poco::Dynamic::Array errorsCollection;
        Poco::DynamicStruct sourceErrorPointer;

    };


} }

#endif

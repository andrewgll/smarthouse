#include "Poco/JSON/Object.h"
#include "server/resource/utils/json_builder.h"

namespace interface {
namespace handling {
    JsonBuilder::JsonBuilder()
        : json()
    { }

    void JsonBuilder::withData(const std::string& key, const std::string& value)
    {
        json.insert(key,value);
    }

    Poco::DynamicStruct & JsonBuilder::JsonBuilder::build()
    {
        return json;
    }
} 
}

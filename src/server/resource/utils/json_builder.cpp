#include "server/resource/utils/json_builder.h"

#include "Poco/JSON/Object.h"

namespace interface {
namespace resource {
namespace utils {
JsonBuilder::JsonBuilder() : json() {}

void JsonBuilder::withData(const std::string& key, const std::string& value) {
  json.insert(key, value);
}

Poco::DynamicStruct& JsonBuilder::JsonBuilder::build() { return json; }
}  // namespace utils
}  // namespace resource
}  // namespace interface

#include "server/resource/utils/json_error_builder.h"

#include "Poco/JSON/Object.h"

namespace interface {
namespace resource {
namespace utils {
JsonErrorBuilder::JsonErrorBuilder(const std::string& url)
    : host(url),
      commonError(),
      rootJsonStructure(),
      errorsCollection(),
      sourceErrorPointer()

{}

void JsonErrorBuilder::withStatusCode(int code) {
  commonError.insert("status", code);
}

void JsonErrorBuilder::withType(const std::string& type) {
  commonError.insert("type", type);
}

void JsonErrorBuilder::withDetails(const std::string& text) {
  commonError.insert("details", text);
}

void JsonErrorBuilder::sourceAt(const std::string& pointer) {
  sourceErrorPointer.insert("pointer", host + pointer);
}

Poco::DynamicStruct& JsonErrorBuilder::build() {
  commonError.insert("source", sourceErrorPointer);
  errorsCollection.push_back(commonError);

  rootJsonStructure.insert("error", errorsCollection);
  return rootJsonStructure;
}
}  // namespace utils
}  // namespace resource
}  // namespace interface

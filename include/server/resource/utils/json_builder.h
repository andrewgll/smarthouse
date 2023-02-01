
#ifndef SmartHouse_Interface_utils_Json_Builder_INCLUDED
#define SmartHouse_Interface_utils_Json_Builder_INCLUDED
#include <string>

#include "Poco/Dynamic/Struct.h"

namespace interface {

namespace resource {
namespace utils {
class JsonBuilder {
 public:
  explicit JsonBuilder();
  ~JsonBuilder() = default;

  Poco::DynamicStruct& build();
  void withData(const std::string&, const std::string&);

 private:
  Poco::DynamicStruct json;
};
}  // namespace utils
}  // namespace resource
}  // namespace interface

#endif

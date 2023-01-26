#ifndef SmartHouse_device_db_service_Included
#define SmartHouse_device_db_service_Included

#include <string>

#include "Poco/Path.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Dynamic/Struct.h"
#include "Poco/JSON/Array.h"
#include "device.h"

namespace db {

class DeviceDBService {
 public:
  DeviceDBService() = default;
  DeviceDBService(Poco::Path);
  void addDevice(const Poco::JSON::Object::Ptr );
  Poco::DynamicStruct findDevice(const std::string&);
  void updateDevice(const std::string&, const Device&);
  void deleteDevice(const std::string&);
  Poco::SharedPtr<Poco::JSON::Array> loadDB();

 private:
  Poco::Path path_;
  size_t lastId_;
};

}  // namespace db

#endif

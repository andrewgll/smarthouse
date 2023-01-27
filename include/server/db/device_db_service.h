#ifndef SmartHouse_device_db_service_Included
#define SmartHouse_device_db_service_Included

#include <string>

#include "Poco/Path.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Dynamic/Struct.h"
#include "Poco/JSON/Array.h"

namespace db {

class  DeviceDBService {
 public:
  DeviceDBService();
  DeviceDBService(Poco::Path);
  void addDevice(Poco::SharedPtr<Poco::JSON::Object>);
  Poco::SharedPtr<Poco::JSON::Object> findDevice(const std::string&);
  void updateDevice(Poco::SharedPtr<Poco::JSON::Object>, const std::string&);
  void deleteDevice(const std::string&);
  Poco::SharedPtr<Poco::JSON::Array> loadDB();

 private:
  Poco::Path path_;
  Poco::JSON::Array::Ptr db;
};

}  // namespace db

#endif

#ifndef SmartHouse_device_db_service_Included
#define SmartHouse_device_db_service_Included

#include <string>
#include "device.h"
#include "Poco/Path.h"

namespace db {

class DeviceDBService {
 public:
 DeviceDBService() = default;
  DeviceDBService(Poco::Path);
  void addDevice(const Device&);
  Device& findDevice(const std::string&);
  void updateDevice(const std::string&, const Device&);
  void deleteDevice(const std::string&);
  

 private:
   Poco::Path path_;
};

}  // namespace db

#endif

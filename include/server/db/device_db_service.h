#ifndef SmartHouse_device_db_service_Included
#define SmartHouse_device_db_service_Included

#include <string>

#include "Poco/JSON/Array.h"
#include "Poco/Path.h"
#include "abstract_db_service.h"

namespace db {

class DeviceDBService : public AbstractDBService {
 public:
  DeviceDBService(Poco::Path);
  void addItem(Poco::SharedPtr<Poco::JSON::Object>) override;
  Poco::SharedPtr<Poco::JSON::Object> findItem(const std::string&) override;
  void updateItem(Poco::SharedPtr<Poco::JSON::Object>,
                  const std::string&) override;
  void deleteItem(const std::string&) override;
};

}  // namespace db

#endif

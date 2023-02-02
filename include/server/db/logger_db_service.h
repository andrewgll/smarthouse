#ifndef SmartHouse_device_db_service_Included
#define SmartHouse_device_db_service_Included

#include <string>

#include "Poco/JSON/Array.h"
#include "Poco/Path.h"
#include "abstract_db_service.h"

namespace db {

class LoggerDBService : public AbstractDBService {
 public:
  LoggerDBService(Poco::Path& path) : AbstractDBService(path){};
};

}  // namespace db

#endif

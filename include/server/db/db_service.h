#ifndef SmartHouse_db_service_Included
#define SmartHouse_db_service_Included

#include <string>

#include "Poco/Dynamic/Struct.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Array.h"
#include "Poco/Path.h"
#include "Poco/URI.h"

namespace db {

class DBService {
 public:
  DBService();
  DBService(Poco::Path);
  void add(Poco::SharedPtr<Poco::JSON::Object>);
  Poco::SharedPtr<Poco::JSON::Array> find(
      const std::vector<std::pair<std::string, std::string>> &);
  void update(Poco::SharedPtr<Poco::JSON::Object>,
              const std::vector<std::pair<std::string, std::string>> &);
  void remove(const std::string &);
  Poco::SharedPtr<Poco::JSON::Array> loadDB();
  void saveDB();
  Poco::SharedPtr<Poco::JSON::Array> getDB();

 private:
  Poco::Path path_;
  Poco::JSON::Array::Ptr db;
};

}  // namespace db

#endif

#ifndef SmartHouse_db_service_Included
#define SmartHouse_db_service_Included

#include <string>

#include "Poco/Path.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Dynamic/Struct.h"
#include "Poco/JSON/Array.h"

namespace db {

class  DBService {
 public:
  DBService();
  DBService(Poco::Path);
  void addItem(Poco::SharedPtr<Poco::JSON::Object>);
  Poco::SharedPtr<Poco::JSON::Object> findItem(const std::string&);
  void updateItem(Poco::SharedPtr<Poco::JSON::Object>, const std::string&);
  void deleteItem(const std::string&);
  Poco::SharedPtr<Poco::JSON::Array> loadDB();
  void saveDB();
 private:
  Poco::Path path_;
  Poco::JSON::Array::Ptr db;
};

}  // namespace db

#endif
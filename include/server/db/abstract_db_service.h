#ifndef SmartHouse_abstract_db_service_Included
#define SmartHouse_abstract_db_service_Included
#include <string>

#include "Poco/JSON/Array.h"
#include "Poco/Path.h"

namespace db {
class AbstractDBService {
 public:
  AbstractDBService();
  AbstractDBService(Poco::Path);

  Poco::SharedPtr<Poco::JSON::Array> loadDB();
  void saveDB();
  Poco::Path getPath() { return pathToDB; };
  virtual void addItem(Poco::SharedPtr<Poco::JSON::Object>);
  virtual Poco::SharedPtr<Poco::JSON::Object> findItem(const std::string&);
  virtual void updateItem(Poco::SharedPtr<Poco::JSON::Object>,
                          const std::string&);
  virtual void deleteItem(const std::string&);

 protected:
  Poco::Path pathToDB;
  Poco::JSON::Array::Ptr db;
};

}  // namespace db
#endif

#include "server/db/abstract_db_service.h"

#include <string>

#include "Poco/Dynamic/Var.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Path.h"
#include "server/resource/utils/exception.h"
#include "server/resource/utils/json_builder.h"

namespace db {
AbstractDBService::AbstractDBService() : pathToDB() {}
AbstractDBService::AbstractDBService(Poco::Path& path) : pathToDB(path) {
  // Initialize db
  db = loadDB();
};

Poco::SharedPtr<Poco::JSON::Array> AbstractDBService::loadDB() {
  Poco::FileInputStream fis(pathToDB.toString());
  Poco::JSON::Parser parser;
  Poco::Dynamic::Var result = parser.parse(fis);
  fis.close();

  return result.extract<Poco::JSON::Array::Ptr>();
}
void AbstractDBService::saveDB() {
  Poco::FileOutputStream fos(pathToDB.toString());
  Poco::JSON::Stringifier::condense(db, fos);
  fos.close();
}
void AbstractDBService::addItem(Poco::JSON::Object::Ptr item) {
  throw "Not implemented db method.";
}
Poco::SharedPtr<Poco::JSON::Object> AbstractDBService::findItem(
    const std::string& id) {
  throw "Not implemented db method.";
}
void AbstractDBService::updateItem(Poco::SharedPtr<Poco::JSON::Object> data,
                                   const std::string& id) {
  throw "Not implemented db method.";
}

void AbstractDBService::deleteItem(const std::string& id) {
  throw "Not implemented db method.";
}

}  // namespace db

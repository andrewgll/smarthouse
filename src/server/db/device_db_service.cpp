
#include "server/db/device_db_service.h"

#include <string>

#include "Poco/Dynamic/Var.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/NumericString.h"
#include "Poco/Path.h"
#include "server/db/device.h"
#include "server/resource/utils/exception.h"
#include "server/resource/utils/json_builder.h"

namespace db {

DeviceDBService::DeviceDBService(Poco::Path path) : path_(path){};

Poco::SharedPtr<Poco::JSON::Array> DeviceDBService::loadDB() {
  try {
    Poco::File File(path_.toString());
    Poco::FileInputStream fis(path_.toString());
    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(fis);
    return result.extract<Poco::JSON::Array::Ptr>();
  } catch (...) {
  }
}

void DeviceDBService::addDevice(const Device& device) {}
Poco::DynamicStruct DeviceDBService::findDevice(const std::string& id) {
  try {
    auto db = DeviceDBService::loadDB();

    for (auto it = db->begin(); it != db->end(); ++it) {
      Poco::JSON::Object::Ptr json = it->extract<Poco::JSON::Object::Ptr>();
      std::string objId = json->getValue<std::string>("id");
      if (objId == id) {
        interface::handling::JsonBuilder builder;
        builder.withData("id", objId);
        builder.withData("name", json->getValue<std::string>("name"));
        builder.withData("type", json->getValue<std::string>("type"));
        builder.withData("status", json->getValue<std::string>("status"));
        return builder.build();
      }
    }
    throw interface::resource::Exception("Not found.", "", 501);
  } catch (const std::exception& exc) {
    throw interface::resource::Exception("DB ERROR;",
                                         "Something went wrong... ", 501);
  }
}
void updateDevice(const db::Device&);
void deleteDevice(const std::string&);
std::string path_;

}  // namespace db

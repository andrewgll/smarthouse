
#include "server/db/device_db_service.h"

#include <string>

#include "Poco/Dynamic/Var.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Path.h"
#include "server/db/device.h"
#include "server/resource/utils/exception.h"
#include "server/resource/utils/json_builder.h"

namespace db {

DeviceDBService::DeviceDBService(Poco::Path path) : path_(path){};

Poco::SharedPtr<Poco::JSON::Array> DeviceDBService::loadDB() {
  Poco::File File(path_.toString());
  Poco::FileStream fis(path_.toString());
  Poco::JSON::Parser parser;
  Poco::Dynamic::Var result = parser.parse(fis);
  return result.extract<Poco::JSON::Array::Ptr>();
}

void DeviceDBService::addDevice(const Poco::DynamicStruct& device) {}
Poco::DynamicStruct DeviceDBService::findDevice(const std::string& id) {
  auto db = DeviceDBService::loadDB();
  Poco::Logger& logger = Poco::Logger::get("SmartHouseLogger");
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
  throw interface::resource::Exception(
      Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST, "Item not found.",
      Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
}
void updateDevice(const db::Device&);
void deleteDevice(const std::string&);
std::string path_;

}  // namespace db

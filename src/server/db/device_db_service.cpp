
#include "server/db/device_db_service.h"

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

DeviceDBService::DeviceDBService(Poco::Path path) : path_(path) {
  // Initialize db
  db = loadDB();
};

Poco::SharedPtr<Poco::JSON::Array> DeviceDBService::loadDB() {
  Poco::FileInputStream fis(path_.toString());
  Poco::JSON::Parser parser;
  Poco::Dynamic::Var result = parser.parse(fis);
  fis.close();
  return result.extract<Poco::JSON::Array::Ptr>();
}
void DeviceDBService::saveDB() {
  Poco::FileOutputStream fos(path_.toString());
  Poco::JSON::Stringifier::condense(db, fos);
  fos.close();
}
void DeviceDBService::addDevice(Poco::JSON::Object::Ptr device) {
  device->set("id", db->size());
  db->add(device);
  saveDB();
}
Poco::SharedPtr<Poco::JSON::Object> DeviceDBService::findDevice(
    const std::string& id) {
  for (auto it = db->begin(); it != db->end(); ++it) {
    Poco::JSON::Object::Ptr json = it->extract<Poco::JSON::Object::Ptr>();
    if (json->getValue<std::string>("id") == id) {
      return it->extract<Poco::JSON::Object::Ptr>();
    }
  }
  throw interface::resource::utils::HttpServerException(
      Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST, "Item not found",
      Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
}
void DeviceDBService::updateDevice(Poco::SharedPtr<Poco::JSON::Object> data,
                                   const std::string& id) {
  for (auto it = db->begin(); it != db->end(); ++it) {
    Poco::JSON::Object::Ptr json = it->extract<Poco::JSON::Object::Ptr>();
    if (json->getValue<std::string>("id") == id) {
      for (auto it2 = data->begin(); it2 != data->end(); it2++) {
        json->set(it2->first, it2->second);
      }
      saveDB();
      return;
    }
  }
  throw interface::resource::utils::HttpServerException(
      Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST, "Item not found",
      Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
}

void DeviceDBService::deleteDevice(const std::string& id) {
  for (auto it = db->begin(); it != db->end(); ++it) {
    Poco::JSON::Object::Ptr json = it->extract<Poco::JSON::Object::Ptr>();
    if (json->getValue<std::string>("id") == id) {
      db->remove(std::stoi(json->getValue<std::string>("id")));
      saveDB();
      return;
    }
  }
  throw interface::resource::utils::HttpServerException(
      Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST, "Item not found",
      Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
}

}  // namespace db

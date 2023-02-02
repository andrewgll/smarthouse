
#include "server/db/device_db_service.h"

#include <string>

#include "Poco/Dynamic/Var.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Path.h"
#include "server/db/abstract_db_service.h"
#include "server/resource/utils/exception.h"
#include "server/resource/utils/json_builder.h"

namespace db {

DeviceDBService::DeviceDBService(Poco::Path& path) : AbstractDBService(path){};
void DeviceDBService::addItem(Poco::JSON::Object::Ptr device) {
  device->set("id", db->size());
  db->add(device);
  saveDB();
}
Poco::SharedPtr<Poco::JSON::Object> DeviceDBService::findItem(
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
void DeviceDBService::updateItem(Poco::SharedPtr<Poco::JSON::Object> data,
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

void DeviceDBService::deleteItem(const std::string& id) {
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

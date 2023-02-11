
#include "server/db/db_service.h"

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

DBService::DBService(Poco::Path path) : path_(path) {
  // Initialize db
  db = loadDB();
};
Poco::JSON::Array::Ptr DBService::getDB() {
  if (db != nullptr) {
    return db;
  }
  throw interface::resource::utils::HttpServerException(
      Poco::Net::HTTPResponse::HTTP_REASON_INTERNAL_SERVER_ERROR,
      "Could not find data base.",
      Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
}
Poco::SharedPtr<Poco::JSON::Array> DBService::loadDB() {
  try {
    Poco::FileInputStream fis(path_.toString());
    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(fis);
    fis.close();
    return result.extract<Poco::JSON::Array::Ptr>();
  } catch (...) {
    throw interface::resource::utils::HttpServerException(
        Poco::Net::HTTPResponse::HTTP_REASON_INTERNAL_SERVER_ERROR,
        "Could not load data base.",
        Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
  }
}

void DBService::saveDB() {
  try {
    Poco::FileOutputStream fos(path_.toString());
    Poco::JSON::Stringifier::condense(db, fos);
    fos.close();
  } catch (...) {
    throw interface::resource::utils::HttpServerException(
        Poco::Net::HTTPResponse::HTTP_REASON_INTERNAL_SERVER_ERROR,
        "Could not save data base.",
        Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
  }
}
bool isAcceptable(
    Poco::JSON::Object::Ptr json,
    const std::vector<std::pair<std::string, std::string>>& params) {
  for (auto itParam = params.begin(); itParam != params.end(); itParam++) {
    try {
      if (json->getValue<std::string>(itParam->first) != itParam->second) {
        return false;
      }
    } catch (...) {
      throw interface::resource::utils::HttpServerException(
          Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST,
          "Invalid parameter.", Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
    }
  }
  return true;
}
Poco::SharedPtr<Poco::JSON::Array> DBService::find(
    const std::vector<std::pair<std::string, std::string>>& params) {
  Poco::JSON::Array::Ptr dbArray = new Poco::JSON::Array();
  for (auto it = db->begin(); it != db->end(); ++it) {
    Poco::JSON::Object::Ptr json = it->extract<Poco::JSON::Object::Ptr>();
    if (isAcceptable(json, params)) {
      dbArray->add(json);
    }
  }
  if (dbArray->size() == 0) {
    throw interface::resource::utils::HttpServerException(
        Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST, "Item not found",
        Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
  }
  return dbArray;
}
void DBService::add(Poco::JSON::Object::Ptr device) {
  device->set("id", std::to_string(db->size()));
  db->add(device);
  saveDB();
}
void DBService::update(
    Poco::SharedPtr<Poco::JSON::Object> data,
    const std::vector<std::pair<std::string, std::string>>& params) {
  bool isFound = false;
  for (auto it = db->begin(); it != db->end(); ++it) {
    Poco::JSON::Object::Ptr json = it->extract<Poco::JSON::Object::Ptr>();
    if (isAcceptable(json, params)) {
      isFound = true;
      for (auto it2 = data->begin(); it2 != data->end(); it2++) {
        json->set(it2->first, it2->second);
      }
    }
  }
  if (isFound) {
    saveDB();
  } else {
    throw interface::resource::utils::HttpServerException(
        Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST, "Item not found",
        Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
  }
}

void DBService::remove(const std::string& id) {

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

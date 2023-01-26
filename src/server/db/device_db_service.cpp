
#include "server/db/device_db_service.h"

#include <string>

#include "Poco/Dynamic/Var.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/Path.h"
#include "server/db/device.h"
#include "server/resource/utils/exception.h"

namespace db {

DeviceDBService::DeviceDBService(Poco::Path path) : path_(path){};

void DeviceDBService::addDevice(const Device& device) {}
db::Device& DeviceDBService::findDevice(const std::string& id) {
  Poco::Logger& logger = Poco::Logger::get("SmartHouseLogger");
  try {
    // JSON Parser need to be implemented......
    Poco::File File(path_.toString());
    Poco::FileInputStream fis(path_.toString());
    Poco::JSON::Parser parser;
    Poco::DynamicAny result;
    result = parser.parse(fis);
    auto object = result.extract<Poco::JSON::Object::Ptr>();
    Poco::Dynamic::Var test =
        object->get("id");  // holds { "property" : "value" }

    logger.information(test.toString());

  } catch (const std::exception& exc) {
    // catch anything thrown within try block that derives from std::exception
    std::cerr << exc.what();
  }
}
void updateDevice(const db::Device&);
void deleteDevice(const std::string&);
std::string path_;

}  // namespace db

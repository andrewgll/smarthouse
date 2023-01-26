#ifndef SmartHouse_device_Included
#define SmartHouse_device_Included

#include <string>

namespace db {

struct Device {
 public:
    std::string id;
    std::string name;
    std::string type;
    std::string state;
};

}  // namespace db

#endif

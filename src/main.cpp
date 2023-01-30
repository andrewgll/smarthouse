#include <iostream>

#include "server/interface/container.h"
#include "server/interface/router.h"

int main(int argc, char* argv[]) {
  try {
    interface::Container container;
    container.setRouter(new interface::Router());
    // Run application with Router as Request Handler Factory
    return container.run(argc, argv);
  } catch (const std::exception& e) {
    std::cout << "there was an error:\n" << e.what();
  } catch(...) {
    std::cout << "there was an error\n";
  }
  return Poco::Util::Application::EXIT_SOFTWARE;
}
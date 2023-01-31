#include <iostream>

#include "server/interface/container.h"

int main(int argc, char* argv[]) {
  try {
    interface::Container container;
    return container.run(argc, argv);
  } catch (const std::exception& e) {
    std::cout << "There was an error:\n" << e.what() << std::endl;
    return Poco::Util::Application::EXIT_SOFTWARE;
  }
}
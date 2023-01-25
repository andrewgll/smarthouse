#include "interface/container.h"
#include "interface/router.h"

int main(int argc, char* argv[]) {
  interface::Container container;

  container.setPort(9090);
  container.setRouter(new interface::Router());
  // Run application with Router as Request Handler Factory
  return container.run(argc, argv);
}
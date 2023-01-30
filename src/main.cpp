#include "server/interface/container.h"
#include "server/interface/router.h"
#include "ServerUI.h"

int main(int argc, char* argv[]) {
  interface::Container container;
  container.setRouter(new interface::Router());
 /* myUI ui;
  ui.Run();*/
  // Run application with Router as Request Handler Factory
  return container.run(argc, argv);
}

#include "Interface/Container.h"
#include "Interface/Router.h"

int main (int argc, char * argv[]) {

    Interface::Container container;

    container.setPort(9090);
    container.setRouter(new Interface::Router());
    //Run application with Router as Request Handler Factory
    return container.run(argc, argv);

}
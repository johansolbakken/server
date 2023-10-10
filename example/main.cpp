#include <server.h>
#include <iostream>

int main() {
    bool running = true;

    Server::ServerSpecification spec;
    spec.port = 8080;
    spec.maxConnections = 10;

    Server::Server server(spec);
    server.addHandler("/", [](){
        std::cout << "Hello World!" << std::endl;
    });

    server.addHandler("/quit", [&running](){
        running = false;
    });

    std::cout << "Server started on http://localhost:" << spec.port << std::endl;

    while (running) {
        server.update();
    }

    server.join();
}
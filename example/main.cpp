#include <server.h>
#include <iostream>

int main() {
    bool running = true;

    Server::ServerSpecification spec;
    spec.port = 8080;
    spec.maxConnections = 10;

    Server::Server server(spec);
    server.get("/", [](Server::Request request){
        return Server::Response{ Server::StatusCode::Ok, "Hello World!" };
    });

    server.get("/status", [&running](Server::Request request){
        return Server::Response{ Server::StatusCode::Ok, "Server is running" };
    });

    server.get("/quit", [&running](Server::Request request){
        running = false;
        return Server::Response{ Server::StatusCode::Ok, "Server is shutting down" };
    });

    std::cout << "Server started on http://localhost:" << spec.port << std::endl;

    while (running) {
        server.update();
    }

    server.join();
}
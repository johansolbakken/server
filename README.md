# server

- Add as submodule
- Link

~~~c++
#include <server.h>
#include <iostream>

int main() {
    bool running = true;

    Server::ServerSpecification spec;
    spec.port = 8080;

    Server::Server server(spec);
    server.get("/", [](Server::Request request){
        return Server::Response{ Server::StatusCode::Ok, "Hello World!" };
    });

    server.get("/quit", [&running](Server::Request request){
        running = false;
        return Server::Response{ Server::StatusCode::Ok, "Server is shutting down" };
    });

    std::cout << "Server started on http://localhost:" << server.port() << std::endl;
    while (running) {
        server.update();
    }
}
~~~

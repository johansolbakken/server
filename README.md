# server

- Add as submodule
- Link

## Server
~~~c++
 #include <knekt.h>
 #include <iostream>

int main() {
    Knekt::ServerSpecification spec;
    spec.port = 8080;

    Knekt::Server server(spec);
    server.get("/", [](Knekt::Request request){
        return Knekt::Response{ Knekt::StatusCode::Ok, "Hello World!" };
    });

    std::cout << "Server started on http://localhost:" << server.port() << std::endl;
    while (true) {
        server.update();
    }
}
~~~

## Client
~~~c++
 #include <knekt.h>
 #include <iostream>

int main() {
    Knekt::Client::get("http://localhost:8080/", [](Knekt::Response response){
        std::cout << response.body << std::endl;
    });
}
~~~

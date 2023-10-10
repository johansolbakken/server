#include <server.h>
#include <iostream>
#include <chrono>
#include <sstream>

#include <thread>


#include <stdlib.h>

int main() {
    bool running = true;

    Knekt::ServerSpecification spec;
    spec.port = 8080;
    spec.maxConnections = 10;
    spec.maxThreads = 10;

    Knekt::Server server(spec);
    server.get("/", [](Knekt::Request request){
        return Knekt::Response{ Knekt::StatusCode::Ok, "Hello World!" };
    });

    server.get("/status", [&running](Knekt::Request request){
        return Knekt::Response{ Knekt::StatusCode::Ok, "Server is running" };
    });

    server.get("/quit", [&running](Knekt::Request request){
        running = false;
        return Knekt::Response{ Knekt::StatusCode::Ok, "Server is shutting down" };
    });

    server.get("/random", [](Knekt::Request request){
        // start time
        auto start = std::chrono::high_resolution_clock::now();
        int random_seconds_from_5_to_10 = rand() % 5 + 5;
        std::this_thread::sleep_for(std::chrono::seconds(random_seconds_from_5_to_10));
        // end time
        auto end = std::chrono::high_resolution_clock::now();
        std::stringstream ss;

        ss << "Started at " << std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count() << std::endl;
        ss << "Ended at " << std::chrono::duration_cast<std::chrono::milliseconds>(end.time_since_epoch()).count() << std::endl;

        ss << "Slept for " << random_seconds_from_5_to_10 << " seconds" << std::endl;
        return Knekt::Response{ Knekt::StatusCode::Ok, ss.str() };
    });

    std::cout << "Server started on http://localhost:" << server.port() << std::endl;
    while (running) {
        server.update();
    }
    server.join();
}
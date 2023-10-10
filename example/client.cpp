#include <client.h>
#include <iostream>
#include <string>

int main() {
    Knekt::Client::get("http://localhost:8080/", [](Knekt::Response response){
        std::cout << response.body << std::endl;
    });
}
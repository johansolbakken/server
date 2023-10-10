#include <client.h>
#include <iostream>
#include <string>

int main() {
    Knekt::Client::get("https://movie-database-alternative.p.rapidapi.com/", [](Knekt::Response response){
        std::cout << response.body << std::endl;
    });
}
cmake_minimum_required(VERSION 3.15)

project(Server)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCE_FILES
        "src/*.cpp"
        "src/*.h")

add_library(server ${SOURCE_FILES})

target_include_directories(server PUBLIC src)

add_executable(example example/main.cpp)
target_link_libraries(example server)
target_include_directories(example PUBLIC src)
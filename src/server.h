#pragma once

#include <functional>
#include <string>
#include <map>

#include "socket.h"

namespace Server {

    using Handler = std::function<void()>;

    struct ServerSpecification {
        int port;
        int maxConnections;
    };

    class Server {
        public:
            Server(const ServerSpecification &specification);
            ~Server();

            void update();
            void join();

            void get(const std::string &path, const Handler &handler);
            void post(const std::string &path, const Handler &handler);

        private:
            ServerSpecification m_specification;
            std::map<std::string, std::map<std::string,Handler>> m_handlers;
            Socket* m_serverSocket = nullptr;
    };
}
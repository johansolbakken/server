#pragma once

#include <functional>
#include <string>
#include <map>

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

            void addHandler(const std::string &path, const Handler &handler);

        private:
            ServerSpecification m_specification;
            std::map<std::string, Handler> m_handlers;
    };
}
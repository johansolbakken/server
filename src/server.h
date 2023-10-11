#pragma once

#include <functional>
#include <string>
#include <map>
#include <vector>

#include "socket.h"
#include "model.h"

namespace Knekt
{
    using Handler = std::function<Response(Request)>;

    struct ServerSpecification
    {
        int port;
        int maxConnections;
        int maxThreads;
    };

    class Server
    {
    public:
        Server(const ServerSpecification &specification);
        ~Server();

        void update();
        void join();

        void get(const std::string &path, const Handler &handler);
        void post(const std::string &path, const Handler &handler);

        int port() const { return m_specification.port; }

    private:
        void dispatch(const std::shared_ptr<Socket> &clientSocket);

    private:
        ServerSpecification m_specification;
        std::map<std::string, std::map<std::string, Handler>> m_handlers;
        Socket *m_serverSocket = nullptr;
    };
}
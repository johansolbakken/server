#pragma once

#include <string>
#include <memory>

namespace Knekt
{
    enum class Domain
    {
        AF_INET = 2,
    };

    enum class SocketType
    {
        SOCK_STREAM = 1,
    };

    struct SocketSpecification
    {
        Domain domain;
        SocketType type;
        int protocol;
        int port;
        int maxConnections;
    };

    class Socket
    {
    public:
        Socket();
        Socket(const SocketSpecification &specification);
        ~Socket();

        void bind();
        void listen();
        std::shared_ptr<Socket> accept();

        std::string read();
        void write(const std::string &data);

        void connect(const std::string &ip);
        void disconnect();

    private:
        SocketSpecification m_specification;
        int m_socket;
    };
}
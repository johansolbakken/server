#include "socket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

namespace Server
{
    Socket::Socket()
    {
    }

    Socket::Socket(const SocketSpecification &spec)
        : m_specification(spec)
    {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0)
        {
            std::cerr << "Failed to create socket" << std::endl;
            exit(1);
        }
    }

    Socket::~Socket()
    {
        close(m_socket);
    }

    void Socket::bind()
    {
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(m_specification.port);
        if (::bind(m_socket, (sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        {
            std::cerr << "Failed to bind socket" << std::endl;
            exit(1);
        }
    }

    void Socket::listen()
    {
        if (::listen(m_socket, m_specification.maxConnections) < 0)
        {
            std::cerr << "Failed to listen on socket" << std::endl;
            exit(1);
        }
    }

    std::shared_ptr<Socket> Socket::accept()
    {
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = ::accept(m_socket, (sockaddr *)&clientAddress, &clientAddressLength);

        if (clientSocket < 0)
        {
            std::cerr << "Failed to accept client connection" << std::endl;
            exit(1);
        }

        auto client = std::make_shared<Socket>();
        client->m_socket = clientSocket;
        return client;
    }

    std::string Socket::read()
    {
        char buffer[1024];
        int bytesReceived = recv(m_socket, buffer, sizeof(buffer), 0);
        if (bytesReceived < 0)
        {
            std::cerr << "Failed to read from socket" << std::endl;
            exit(1);
        }

        return std::string(buffer, bytesReceived);
    }

    void Socket::write(const std::string &data)
    {
        send(m_socket, data.c_str(), data.size(), 0);
    }
}
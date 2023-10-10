#include "server.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <iostream>
#include <sstream>

namespace Server
{
    Server::Server(const ServerSpecification &specification)
        : m_specification(specification)
    {
        m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_serverSocket < 0)
        {
            std::cerr << "Failed to create socket" << std::endl;
            exit(1);
        }

        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(m_specification.port);
        if (bind(m_serverSocket, (sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        {
            std::cerr << "Failed to bind socket" << std::endl;
            exit(1);
        }

        if (listen(m_serverSocket, m_specification.maxConnections) < 0)
        {
            std::cerr << "Failed to listen on socket" << std::endl;
            exit(1);
        }
    }

    Server::~Server()
    {
        close(m_serverSocket);
    }

    void Server::update()
    {
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(m_serverSocket, (sockaddr *)&clientAddress, &clientAddressLength);

        if (clientSocket < 0)
        {
            std::cerr << "Failed to accept client connection" << std::endl;
            exit(1);
        }

        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived < 0)
        {
            std::cerr << "Failed to read from socket" << std::endl;
            exit(1);
        }

        std::string request(buffer, bytesReceived);
        std::string method, path;
        std::stringstream ss(request);
        ss >> method >> path;
        //std::cout << method << " \"" << path << "\"" << std::endl;

        // find handler
        Handler handler = m_handlers[method][path];
        if (handler)
        {
            handler();
            std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello World!";
            send(clientSocket, response.c_str(), response.size(), 0);
        }
        else
        {
            std::string response = "HTTP/1.1 404 Not Found\r\nContent-Length: 9\r\n\r\nNot Found";
            send(clientSocket, response.c_str(), response.size(), 0);
        }

        close(clientSocket);
    }

    void Server::join()
    {
    }

    void Server::get(const std::string &path, const Handler &handler)
    {
        m_handlers["GET"][path] = handler;
    }

    void Server::post(const std::string &path, const Handler &handler)
    {
        m_handlers["POST"][path] = handler;
    }
}
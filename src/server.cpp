#include "server.h"

#include <iostream>
#include <sstream>

#include "socket.h"

namespace Server
{
    Server::Server(const ServerSpecification &specification)
        : m_specification(specification)
    {
        SocketSpecification spec;
        spec.domain = Domain::AF_INET;
        spec.type = SocketType::SOCK_STREAM;
        spec.protocol = 0;
        spec.port = m_specification.port;
        spec.maxConnections = m_specification.maxConnections;
        
        m_serverSocket = new Socket(spec);
        m_serverSocket->bind();
        m_serverSocket->listen();
    }

    Server::~Server()
    {
        delete m_serverSocket;
    }

    void Server::update()
    {
        Socket clientSocket = m_serverSocket->accept();
        std::string request = clientSocket.read();

        std::string method, path;
        std::stringstream ss(request);
        ss >> method >> path;

        Handler handler = m_handlers[method][path];
        if (handler)
        {
            handler();
            std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello World!";
            clientSocket.write(response);
        }
        else
        {
            std::string response = "HTTP/1.1 404 Not Found\r\nContent-Length: 9\r\n\r\nNot Found";
            clientSocket.write(response);
        }
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
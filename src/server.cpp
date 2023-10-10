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

        std::string method, path, version, status, statusMessage, header, body;
        std::stringstream ss(request);
        ss >> method >> path >> version;

        body = request.substr(request.find("\r\n\r\n") + 4);

        Request req;
        req.method = method;
        req.path = path;
        req.body = body;

        Handler handler = m_handlers[method][path];
        Response res;
        if (handler)
        {
            res = handler(req);
        } else {
            res = { StatusCode::NotFound, "Not found" };
        }

        std::stringstream response;
        response << "HTTP/1.1 " << (int)res.statusCode << " " << (int)res.statusCode << "\r\n";
        response << "Content-Type: application/json\r\n";
        response << "Content-Length: " << res.body.length() << "\r\n";
        response << "\r\n";
        response << res.body;

        clientSocket.write(response.str());
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
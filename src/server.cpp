#include "server.h"

namespace Server
{
    Server::Server(const ServerSpecification& specification)
        : m_specification(specification)
    {

    }

    Server::~Server()
    {

    }

    
    void Server::update()
    {

    }

    void Server::join()
    {

    }

    void Server::addHandler(const std::string &path, const Handler &handler)
    {
        m_handlers[path] = handler;
    }
}
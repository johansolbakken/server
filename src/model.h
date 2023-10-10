#pragma once

namespace Knekt
{
    struct Request
    {
        std::string method;
        std::string path;
        // std::map<std::string, std::string> headers; // TODO(johan) implement
        // std::map<std::string, std::string> query;
        std::string body;
    };

    enum class StatusCode
    {
        Ok = 200,
        NotFound = 404,
        InternalServerError = 500,
    };

    struct Response
    {
        StatusCode statusCode;
        std::string body;
    };
}
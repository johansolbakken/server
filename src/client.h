#pragma once

#include <string>
#include <functional>

#include "model.h"

namespace Knekt
{
    using Callback = std::function<void(Response)>;

    class Client
    {
    public:
        static void get(const std::string &url, const Callback &callback);
    };
}
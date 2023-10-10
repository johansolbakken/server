#include "client.h"
#include <iostream>
#include <string>
#include <curl/curl.h>

namespace Knekt {

    // Callback function to write received data into a string
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
        size_t total_size = size * nmemb;
        output->append(static_cast<char*>(contents), total_size);
        return total_size;
    }

    void Client::get(const std::string& url, const Callback& callback) {
        CURL* curl;
        CURLcode res;
        std::string response_data;
        long response_code;

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();

        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
            } else {
                // Get the HTTP response code
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            }

            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();

        Response response;
        response.body = response_data;
        response.statusCode = static_cast<StatusCode>(response_code);
        callback(response);
    }
}

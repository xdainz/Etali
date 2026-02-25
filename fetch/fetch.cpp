#include "fetch.hpp"

const std::string BASE_URL = "https://api.scryfall.com/cards/";

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp){
    size_t real_size = size * nmemb;
    std::string *buf = static_cast<std::string*>(userp);
    buf->append(static_cast<char*>(contents), real_size);
    return real_size;
}

std::string fetch_single(std::string args){

    if (args == ""){
        args = "random?q=is%3Acommander";
    }

    const std::string API_URL = BASE_URL + args;

    CURL *curl = curl_easy_init();
    std::string response_body;

    if(!curl){
        return std::string("ERROR:1");
    }

    // set headers
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: */*");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Etali/0.1");

    // set url (use c_str())
    curl_easy_setopt(curl, CURLOPT_URL, API_URL.c_str());

    // set write callback to capture response body
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

    CURLcode res = curl_easy_perform(curl);

    // cleanup
    if(headers) curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if(res != CURLE_OK){
        return std::string("ERROR:") + std::to_string((int)res);
    }

    return response_body;

}
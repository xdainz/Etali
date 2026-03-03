#include "fetch.hpp"

const std::string BASE_URL = "https://api.scryfall.com/cards/";
const std::string USER_AGENT = "Etali/"+ VERSION;

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp){
    size_t real_size = size * nmemb;
    std::string *buf = static_cast<std::string*>(userp);
    buf->append(static_cast<char*>(contents), real_size);
    return real_size;
}

static CURL* set_curl(){
    CURL* curl = curl_easy_init();
    // set headers
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: */*");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT.c_str());

    // set write callback to capture response body
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    return curl;
}

std::string fetch_search(std::string query){
    const std::string API_URL = BASE_URL + "search?q=" + query;
    CURL *curl = set_curl();
 
    std::string response_body;
    if(!curl){
        return {"ERROR:1"};
    }

    // set url (use c_str())
    curl_easy_setopt(curl, CURLOPT_URL, API_URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);
    
    CURLcode res = curl_easy_perform(curl);

    // cleanup
    curl_easy_cleanup(curl);

    if(res != CURLE_OK){
        std::cout << API_URL;
        std::cout << response_body;
        return {"ERROR:" + std::to_string((int)res)};
    }
    
    return {response_body};
   
}

std::string fetch_random_commander(std::string args){
    const std::string API_URL = BASE_URL + "random?q=is%3Acommander";
    std::string response_body;
    CURL* curl = set_curl();

    if(!curl){
        return std::string("ERROR:1");
    }
    // set url (use c_str())
    curl_easy_setopt(curl, CURLOPT_URL, API_URL.c_str());
    // set write callback to capture response body
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

    CURLcode res = curl_easy_perform(curl);

    // cleanup
    curl_easy_cleanup(curl);

    if(res != CURLE_OK){
        return std::string("ERROR:") + std::to_string((int)res);
    }

    return response_body;

}
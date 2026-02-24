#include <iostream>
#include <curl/curl.h>

int main(){
    const char *API_URL = "https://api.scryfall.com/cards/random?q=is%3Acommander";
    
    CURL *curl;
    curl = curl_easy_init();

    if(curl){
        // set headers
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: */*");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Etali/0.1");

        // set url
        curl_easy_setopt(curl, CURLOPT_URL, API_URL);
    
        CURLcode response = curl_easy_perform(curl);
    
        std::cout << response;
    }

    return 0;
}
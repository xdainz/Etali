#include "parse_json.hpp"

ScryfallCard parse_json(std::string raw){

    Json::CharReaderBuilder b;
    std::string errs;
    Json::Value root;
    std::unique_ptr<Json::CharReader> reader(b.newCharReader());
    bool ok = reader->parse(raw.c_str(), raw.c_str() + raw.size(), &root, &errs);

    if(!ok){
        std::cout << "ERROR: Unexpected response:  " << raw << std::endl;
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
    }

    if(root.isObject() && root.isMember("object") && root["object"].asString() == "card"){
        ScryfallCard card = parse_card(root);
        return card;
    }
    
    return {};
 
};
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <json/json.h>

struct ScryfallCard {
    std::string object; // "card"
    std::string id;
    std::string oracle_id;
    std::vector<int> multiverse_ids;
    std::string name;
    std::string lang;
    std::string uri;
    std::string scryfall_uri;
    std::string layout;
    
    // Core Data
    int cmc = 0;
    std::string type_line;
    std::string oracle_text;
    std::string mana_cost;
    std::vector<std::string> colors;
    std::vector<std::string> color_identity;
    
    // Imagery
    std::map<std::string, std::string> image_uris; // e.g., small, normal, png
    
    // Sets and Legality
    std::string set;
    std::string set_name;
    std::string collector_number;
    bool digital = false;
    std::map<std::string, std::string> legalities; // e.g., standard: "legal"
};

static ScryfallCard parse_card(const Json::Value &v){
    ScryfallCard c;
    if(!v.isObject()) return c;
    if(v.isMember("object")) c.object = v["object"].asString();
    if(v.isMember("id")) c.id = v["id"].asString();
    if(v.isMember("oracle_id")) c.oracle_id = v["oracle_id"].asString();
    if(v.isMember("name")) c.name = v["name"].asString();
    if(v.isMember("lang")) c.lang = v["lang"].asString();
    if(v.isMember("uri")) c.uri = v["uri"].asString();
    if(v.isMember("scryfall_uri")) c.scryfall_uri = v["scryfall_uri"].asString();
    if(v.isMember("layout")) c.layout = v["layout"].asString();
    if(v.isMember("cmc")) c.cmc = v["cmc"].asInt();
    if(v.isMember("type_line")) c.type_line = v["type_line"].asString();
    if(v.isMember("oracle_text")) c.oracle_text = v["oracle_text"].asString();
    if(v.isMember("mana_cost")) c.mana_cost = v["mana_cost"].asString();
    if(v.isMember("set")) c.set = v["set"].asString();
    if(v.isMember("set_name")) c.set_name = v["set_name"].asString();
    if(v.isMember("collector_number")) c.collector_number = v["collector_number"].asString();
    if(v.isMember("digital")) c.digital = v["digital"].asBool();

    if(v.isMember("multiverse_ids") && v["multiverse_ids"].isArray()){
        for(const auto &m : v["multiverse_ids"]){
            if(m.isInt()) c.multiverse_ids.push_back(m.asInt());
        }
    }

    if(v.isMember("colors") && v["colors"].isArray()){
        for(const auto &col : v["colors"]) if(col.isString()) c.colors.push_back(col.asString());
    }
    if(v.isMember("color_identity") && v["color_identity"].isArray()){
        for(const auto &ci : v["color_identity"]) if(ci.isString()) c.color_identity.push_back(ci.asString());
    }

    if(v.isMember("image_uris") && v["image_uris"].isObject()){
        const Json::Value &imgs = v["image_uris"];
        for(const auto &name : imgs.getMemberNames()){
            c.image_uris[name] = imgs[name].asString();
        }
    }

    if(v.isMember("legalities") && v["legalities"].isObject()){
        const Json::Value &leg = v["legalities"];
        for(const auto &name : leg.getMemberNames()){
            c.legalities[name] = leg[name].asString();
        }
    }

    return c;
}

static std::string card_to_string(const ScryfallCard &c){
    std::ostringstream ss;
    ss << "Name: " << c.name << std::endl;
    ss << "Type: " << c.type_line << std::endl;
    ss << "Mana Cost: " << c.mana_cost << "  CMC: " << c.cmc << std::endl;
    if(!c.colors.empty()){
        ss << "Color Identity: ";
        for(size_t i=0;i<c.colors.size();++i){ if(i) ss << ", "; ss << c.colors[i]; }
        ss << std::endl;
    }
    if(!c.oracle_text.empty()) ss << "Oracle: " << c.oracle_text << std::endl;
    ss << "Set: " << c.set_name << " (" << c.set << ")" << " #" << c.collector_number;
    return ss.str();
}
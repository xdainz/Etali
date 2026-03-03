#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <json/json.h>

struct CardFace {
    std::string object;
    std::string name;
    std::string mana_cost;
    std::string type_line;
    std::string oracle_text;
    std::string flavor_text;
    std::vector<std::string> colors;
    std::vector<std::string> color_indicator;
    std::string power;
    std::string toughness;
    std::string artist;
    std::string artist_id;
    std::string illustration_id;
    std::map<std::string, std::string> image_uris;
};

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
    
    // Multi-faced cards
    std::vector<CardFace> card_faces;
};

static CardFace parse_card_face(const Json::Value &f){
    CardFace face;
    if(!f.isObject()) return face;
    if(f.isMember("object")) face.object = f["object"].asString();
    if(f.isMember("name")) face.name = f["name"].asString();
    if(f.isMember("mana_cost")) face.mana_cost = f["mana_cost"].asString();
    if(f.isMember("type_line")) face.type_line = f["type_line"].asString();
    if(f.isMember("oracle_text")) face.oracle_text = f["oracle_text"].asString();
    if(f.isMember("flavor_text")) face.flavor_text = f["flavor_text"].asString();
    if(f.isMember("power")) face.power = f["power"].asString();
    if(f.isMember("toughness")) face.toughness = f["toughness"].asString();
    if(f.isMember("artist")) face.artist = f["artist"].asString();
    if(f.isMember("artist_id")) face.artist_id = f["artist_id"].asString();
    if(f.isMember("illustration_id")) face.illustration_id = f["illustration_id"].asString();

    if(f.isMember("colors") && f["colors"].isArray()){
        for(const auto &col : f["colors"]) if(col.isString()) face.colors.push_back(col.asString());
    }
    if(f.isMember("color_indicator") && f["color_indicator"].isArray()){
        for(const auto &ci : f["color_indicator"]) if(ci.isString()) face.color_indicator.push_back(ci.asString());
    }
    if(f.isMember("image_uris") && f["image_uris"].isObject()){
        const Json::Value &imgs = f["image_uris"];
        for(const auto &name : imgs.getMemberNames()){
            face.image_uris[name] = imgs[name].asString();
        }
    }
    return face;
}

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

    if(v.isMember("card_faces") && v["card_faces"].isArray()){
        for(const auto &face : v["card_faces"]){
            c.card_faces.push_back(parse_card_face(face));
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
    
    // Handle multi-faced cards
    if(!c.card_faces.empty()){
        for(size_t i=0; i<c.card_faces.size(); ++i){
            const CardFace &face = c.card_faces[i];
            ss << "\n--- Face " << (i+1) << ": " << face.name << " ---" << std::endl;
            if(!face.type_line.empty()) ss << "Type: " << face.type_line << std::endl;
            if(!face.mana_cost.empty()) ss << "Mana Cost: " << face.mana_cost << std::endl;
            if(!face.power.empty() && !face.toughness.empty())
                ss << "P/T: " << face.power << "/" << face.toughness << std::endl;
            if(!face.oracle_text.empty()) ss << "Oracle: " << face.oracle_text << std::endl;
        }
    } else if(!c.oracle_text.empty()){
        ss << "Oracle: " << c.oracle_text << std::endl;
    }
    
    ss << "Set: " << c.set_name << " (" << c.set << ")" << " #" << c.collector_number;
    return ss.str();
}

#endif
#include "parse_json.hpp"

ScryfallCard parse_json(const std::string &raw) {

    Json::CharReaderBuilder b;
    std::string errs;
    Json::Value root;
    std::unique_ptr<Json::CharReader> reader(b.newCharReader());
    bool ok =
        reader->parse(raw.c_str(), raw.c_str() + raw.size(), &root, &errs);

    if (!ok) {
        std::cout << "ERROR: Unexpected response:  " << raw << std::endl;
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
    }

    if (root.isObject() && root.isMember("object") &&
        root["object"].asString() == "card") {
        ScryfallCard card = parse_card(root);
        return card;
    }

    return {};
}

std::vector<ScryfallCard> parse_multiple(const std::string &raw) {

    Json::CharReaderBuilder b;
    std::string errs;
    Json::Value root;
    std::unique_ptr<Json::CharReader> reader(b.newCharReader());
    bool ok =
        reader->parse(raw.c_str(), raw.c_str() + raw.size(), &root, &errs);

    if (!ok) {
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
        return {};
    }

    if (root.isObject() && root.isMember("object") &&
        root["object"].asString() == "list") {

        std::vector<ScryfallCard> card_list;
        const Json::Value &data = root["data"];

        for (const auto &cardJson : data) {
            card_list.push_back(parse_card(cardJson));
        }

        return card_list;
    }

    std::cerr << "Unexpected non-list JSON response in parse_multiple" << std::endl;
    return {};
}
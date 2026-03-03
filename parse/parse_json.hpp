#ifndef PARSE_JSON_H 
#define PARSE_JSON_H 


#include <json/json.h>
#include "../model/card.h"
#include <iostream>

ScryfallCard parse_json(const std::string &raw);
std::vector<ScryfallCard> parse_multiple(const std::string &raw);

#endif
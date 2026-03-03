#include <iostream>
#include "fetch/fetch.hpp"
#include "parse/parse_json.hpp"
#include "cli/help.hpp"


void print_version() {
    std::cout << "Etali v" << VERSION << std::endl;
}

void print_random_commander() {
    std::string response = fetch_random_commander("");
    
    ScryfallCard card_object = parse_json(response);
    
    std::cout << card_to_string(card_object) << std::endl;
}

void print_search(std::string query) {
    std::string response = fetch_search(query);
    
    std::vector<ScryfallCard> card_list = parse_multiple(response);
    
    for (const auto& card: card_list){
        std::cout << card_to_string(card) << std::endl;
        std::cout << std::endl;
    }

}

std::string clean_search(std::string query){
    std::string cleaned_query;

    for (char c: query){
       if (c == ' '){
        cleaned_query += "%20";
       } else {
        cleaned_query += c;
       } 
    }
    
    return cleaned_query;
}

int main(int argc, char* argv[]) {
    
    if (argc <= 1){
        print_random_commander();
        return 0;
    }
    
    std::string command = argv[1];
    
    if (command == "-h" | command == "--help"){
        print_help();
        return 0;

    } else if (command == "-v" | command == "--version"){
        print_version();
        return 0;

    } else if(command == "-s" | command == "--search"){
        if (argc <=2){
            std::cout << "error: missing args" << std::endl << "  try: etali --help";
            return 1;
        } else if (argc > 3){
            std::cout << "error: too many args" << std::endl << "  usage: use quotes when your query has many args";
            return 1;
        } else {
            print_search(clean_search(argv[2]));
            return 0;
        }
        
    } else {
        std::cout << "error: invalid option '"<< command << "'" << std::endl;
    }
    
}
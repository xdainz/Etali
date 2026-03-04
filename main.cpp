#include <cctype>
#include <cstdio>
#include <iostream>
#include "fetch/fetch.hpp"
#include "parse/parse_json.hpp"
#include "cli/help.hpp"


void print_version() {
    std::cout << "Etali v" << VERSION << std::endl;
}

void open_vim(const std::string &data) {
    // input long ahh response from api into a file and
    // open it in vim for the user
    // Errors are encoded with "ERROR:" prefix; print them directly instead of opening vim
    if (data.rfind("ERROR:", 0) == 0) {
        std::cout << data << std::endl;
        return;
    }

    FILE* vim = popen("vim -MR -", "w");
    
    if (vim) {
        fputs(data.c_str(), vim);
        pclose(vim);
    }
}

void print_random_commander() {
    std::string response = fetch_random_commander();
    
    ScryfallCard card_object = parse_json(response);
    
    std::cout << card_to_string(card_object) << std::endl;
}

std::string print_search(std::string query) {
    std::string response = fetch_search(query);
    
    std::vector<ScryfallCard> card_list = parse_multiple(response);
    
    std::string output;
    
    for (const auto& card: card_list){
        output += "---------------------------------------------------------------------------\n";
        output += card_to_string(card) + "\n";
    }
    output += "---------------------------------------------------------------------------\n";

    return output;

}

std::string clean_search(const std::string &query){
    std::string cleaned_query;

    for (unsigned char c : query){
       if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~' || c == ':'){
        cleaned_query += c;
       } else {
        char hex[4];
        snprintf(hex, sizeof(hex), "%%%02X", c);
        cleaned_query += hex;
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
    
    if (command == "-h" || command == "--help"){
        print_help();
        return 0;

    } else if (command == "-v" || command == "--version"){
        print_version();
        return 0;

    } else if(command == "-s" || command == "--search"){
        if (argc <=2){
            std::cout << "error: missing args" << std::endl << "  try: etali --help";
            return 1;
        } else if (argc > 3){
            std::cout << "error: too many args" << std::endl << "  usage: use quotes when your query has many args";
            return 1;
        } else {
            open_vim(print_search(clean_search(argv[2])));
            return 0;
        }

    } else {
        std::cout << "error: invalid option '"<< command << "'" << std::endl;
        return 1;
    }
    
}
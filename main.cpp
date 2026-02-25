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
    } else {
        std::cout << "error: invalid option '"<< command << "'" << std::endl;
    }
    
}
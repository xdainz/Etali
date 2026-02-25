#include "help.hpp"

const std::string VERSION = "0.0.1";

struct Command {
    std::string name;
    std::string details;
};

void print_help() {
    
    std::vector<Command> commands = {
        {"", "Get a random commander"},
        {"{-h --help}", "Print this help message"},
        {"{-v --version}", "Print version information"},
        //{"{-s --search} <query>", "Search for a card"},
    };

    std::cout << "usage:\tetali <operation>" << std::endl;
    std::cout << "operations:" << std::endl;
    
    const int name_column_width = 30;
    const int details_column_width = 30;
    
    for (const Command& c: commands){
        std::string formatted_name = "  etali " + c.name;
        std::cout << std::left << std::setw(name_column_width) << formatted_name;
        std::cout << std::right << std::setw(details_column_width) << c.details << std::endl;
    }
}
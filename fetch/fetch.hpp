#ifndef FETCH_H
#define FETCH_H

#include <string>
#include <curl/curl.h>
#include "../cli/help.hpp"

std::string fetch_random_commander(const std::string &args);
std::string fetch_search(const std::string &search_terms);

#endif
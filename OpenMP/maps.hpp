#ifndef MAPS_HPP
#define MAPS_HPP

#include <iostream>
#include <string>
#include <string.h>
#include <unordered_map>

using namespace std;

class Maps{
    public:
        unordered_map<string, int> maps[12];
        int maps_length[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int search_element_code(std::string, int);
        void add_element(std::string&, int);
        int map_length(int);
};

#endif
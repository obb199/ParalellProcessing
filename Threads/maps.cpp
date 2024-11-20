#include "maps.hpp"

int Maps::search_element_code(std::string str, int i) {
    auto res = maps[i].find(str);
    if (res != maps[i].end()){
        return res->second;
    }
    return -1;
}

void Maps::add_element(std::string &str, int i){
    maps[i].insert({str, maps_length[i]});
    maps_length[i]++;
}

int Maps::map_length(int i){
    return maps_length[i];
}

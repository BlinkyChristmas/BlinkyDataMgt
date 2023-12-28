//Copyright © 2023 Charles Kerr. All rights reserved.

#include "inputlist.hpp"

#include <algorithm>
#include <stdexcept>
#include <fstream>

#include "utility/strutil.hpp"
using namespace std::string_literals ;

//======================================================================
InputList::InputList(const std::filesystem::path &path) :InputList() {
    auto input = std::ifstream(path.string()) ;
    if (!input.is_open()){
        throw std::runtime_error("Unable to open: "s + path.string()) ;
    }
    load(input) ;
}

//======================================================================
auto InputList::load(std::istream &input) -> void {
    constexpr auto LINESIZE = 4096 ;
    auto buffer = std::vector<char>(LINESIZE,0) ;
    
    inputs = std::vector<std::filesystem::path>() ;
    
    while(input.good() && !input.eof()) {
        input.getline( buffer.data(),buffer.size() -1) ;
        if (input.gcount() > 0) {
            buffer[input.gcount()] = 0 ;
            std::string line = buffer.data() ;
            line = util::trim(util::strip(line,"//")) ;
            if (!line.empty()) {
                inputs.push_back(std::filesystem::path(line)) ;
            }
        }
    }
}


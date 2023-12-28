//Copyright © 2023 Charles Kerr. All rights reserved.

#include "chunk.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
Chunk::Chunk():oldIndex(0),newIndex(0),length(0){
    
}

//======================================================================
Chunk::Chunk(const std::string &line):Chunk() {
    auto values = util::parse(line,",") ;
    try{
        switch(values.size()) {
            default:
            case 4:
                label = values[3];
                [[fallthrough]];
            case 3:
                length = std::stoi(values[2]) ;
                [[fallthrough]] ;
            case 2:
                newIndex = std::stoi(values[1]);
                [[fallthrough]];
            case 1:
                oldIndex = std::stoi(values[0]);
                [[fallthrough]];
            case 0:
                break;
        }
    }
    catch(...) {
        throw std::runtime_error("Error parsing chunk line: "s + line);
    }
}

//======================================================================
auto Chunk::maxOffset() const -> int {
    return newIndex + length ;
}

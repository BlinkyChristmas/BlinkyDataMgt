//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef chunk_hpp
#define chunk_hpp

#include <cstdint>
#include <iostream>
#include <string>

//======================================================================
struct Chunk {
    int oldIndex ;
    int newIndex ;
    int length ;
    std::string label ;
    Chunk() ;
    Chunk(const std::string &line) ;
    auto maxOffset() const -> int ;
};

#endif /* chunk_hpp */

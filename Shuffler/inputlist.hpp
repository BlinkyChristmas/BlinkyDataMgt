//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef inputlist_hpp
#define inputlist_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include <filesystem>
#include <istream>
#include <vector>

//======================================================================
struct InputList {
    std::vector<std::filesystem::path> inputs ;
    
    InputList() = default ;
    InputList(const std::filesystem::path &path) ;
    
    auto load(std::istream &input) -> void ;
    
    auto frameCount(const std::filesystem::path &filepath) const -> int ;
};

#endif /* inputlist_hpp */

//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef sourcesection_hpp
#define sourcesection_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <istream>
#include <ostream>

#include "chunk.hpp"
//======================================================================
struct SourceSection {
    std::filesystem::path inputLocation ;
    std::vector<Chunk> chunks ;
    std::string label ;
    
    SourceSection() = default ;
    SourceSection(const std::string label) ;
    SourceSection(const std::string label, std::istream &input);
    auto load(std::istream &input) -> void ;
    
    auto maxIndex() const -> int ;
    
    auto describe() const -> std::string ;
};

#endif /* sourcesection_hpp */

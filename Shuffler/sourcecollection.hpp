//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef sourcecollection_hpp
#define sourcecollection_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include <istream>
#include <vector>
#include <filesystem>

#include "sourcesection.hpp"
//======================================================================
struct SourceCollection {
    std::vector<SourceSection> sources ;
    
    SourceCollection()  = default ;
    SourceCollection(const std::filesystem::path &path) ;
    
    auto load(std::istream &input) ->void ;
    
    auto frameLength() const -> int ;
    
    auto frameCount(const std::filesystem::path &filepath) const -> int ;
    
    auto processFor(const std::filesystem::path  &inputFile, std::iostream &output) const -> void ;
};

#endif /* sourcecollection_hpp */

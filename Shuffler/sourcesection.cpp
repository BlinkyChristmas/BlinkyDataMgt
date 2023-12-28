//Copyright © 2023 Charles Kerr. All rights reserved.

#include "sourcesection.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
SourceSection::SourceSection(const std::string label): label(label){
    
}

//======================================================================
SourceSection::SourceSection(const std::string label, std::istream &input):SourceSection(label) {
    this->load(input) ;
}

//======================================================================
auto SourceSection::load(std::istream &input) -> void {
    constexpr auto LINESIZE = 4096 ;
    
    chunks = std::vector<Chunk>() ;
    
    auto buffer = std::vector<char>(LINESIZE,0) ;
    
    while( input.good() && !input.eof() ) {
        input.getline(buffer.data(),buffer.size()-1) ;
        if (input.gcount() > 0) {
            buffer[input.gcount()] = 0 ;
            std::string line = buffer.data() ;
            line = util::trim(util::strip(line,"//")) ;
            if (!line.empty()){
                
                if (line[0] ==  '}') {
                    // end of section, return
                    break;
                 }
                else {
                    auto [key,value] = util::split(line,"=") ;
                    if ((util::lower(key) == "chunk") && !value.empty()) {
                        chunks.push_back(Chunk(value)) ;
                    }
                    else if (util::lower(key) == "input") {
                        inputLocation = std::filesystem::path(value) ;
                    }
                }
            }
        }
    }
}

//======================================================================
auto SourceSection::maxIndex() const -> int {
    auto index = 0 ;
    for (const auto &entry:chunks){
        index = std::max(index,entry.maxOffset());
    }
    return index ;
}

//======================================================================
auto SourceSection::describe() const -> std::string {
    return "MaxIndex: "s + std::to_string(maxIndex())+ " "s + inputLocation.string() ;
}

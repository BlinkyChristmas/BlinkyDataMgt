//Copyright © 2023 Charles Kerr. All rights reserved.

#include "sourcecollection.hpp"

#include <algorithm>
#include <stdexcept>
#include <fstream>

#include "utility/strutil.hpp"
#include "containers/lightfile/lightheader.hpp"

using namespace std::string_literals ;

//======================================================================
SourceCollection::SourceCollection(const std::filesystem::path &path) : SourceCollection() {
    auto input = std::ifstream( path.string() );
    if (! input.is_open() ) {
        throw std::runtime_error( "Unable to open: "s + path.string() );
    }
    load(input) ;
}

//======================================================================
auto SourceCollection::load(std::istream &input) ->void  {
    constexpr auto LINESIZE = 4096 ;
    
    auto buffer = std::vector<char>(LINESIZE,0) ;
    
    sources = std::vector<SourceSection>() ;
    
    while(input.good() && !input.eof() ) {
        input.getline(buffer.data(),buffer.size()-1) ;
        if (input.gcount() > 0) {
            buffer[input.gcount()] = 0 ;
            std::string line = buffer.data() ;
            line = util::trim(util::strip(line,"//")) ;
            if (!line.empty()){
                if (line[0] == '[' && line[line.size()-1] == ']') {
                    auto contents = util::trim(util::contentsOf(line, "[", "]")) ;
                    auto [name,type] = util::split(contents,":") ;
                    if (util::lower(type) == "source") {
                        sources.push_back(SourceSection(name, input)) ;
                    }
                }
            }
        }
    }
}

//======================================================================
auto SourceCollection::frameLength() const -> int {
    auto length = 0 ;
    for (const auto &entry:sources) {
        length = std::max(length,entry.maxIndex()) ;
    }
    return length ;
}

//======================================================================
auto SourceCollection::frameCount(const std::filesystem::path &filepath) const -> int {
    constexpr auto countOffset = 5 ;
    
    auto maxCount = 0 ;
    
    auto count = 0 ;
    for (const auto &entry:sources) {
        auto path = entry.inputLocation / filepath ;
        auto input = std::ifstream(path.string() , std::ios::binary) ;
        if (!input.is_open()) {
            throw std::runtime_error("Unable to open: "s+path.string());
        }
        input.seekg(countOffset,std::ios::beg) ;
        input.read(reinterpret_cast<char*>(&count),4) ;
        if (input.gcount()!= 4) {
            throw std::runtime_error("Error getting frame count from: "s + path.string());
        }
        maxCount = std::max(maxCount,count) ;
    }
    return maxCount ;
}

//======================================================================
auto SourceCollection::processFor(const std::filesystem::path  &inputFile, std::iostream &output) const -> void {
    
    // Get the output frame length
    LightHeader outHeader ;
    output.seekg(0, std::ios::beg) ;
    outHeader.load(output) ;

    // Cycle through all the sources/chunks
    for (const auto &entry:sources){
        std::cout <<"\tProcessing source: " << entry.label << "\n";
        auto input = std::ifstream((entry.inputLocation / inputFile).string(),std::ios::binary) ;
        if (!input.is_open()) {
            throw std::runtime_error("Unable to open: "s + (entry.inputLocation / inputFile).string());
        }
        LightHeader inputHeader ;
        inputHeader.load(input) ;
        // get the frame length and frame count from the input source
        outHeader.sampleRate = inputHeader.sampleRate ;
        outHeader.sourceName = inputHeader.sourceName ;
        output.seekp(0,std::ios::beg) ;
        outHeader.write(output) ;
        // Now cycle through all the chunks
        for (const auto &chunk:entry.chunks) {
            auto buffer = std::vector<char>(chunk.length,0) ;
            std::cout << "\t\tProcessing chunk: " << chunk.label << std::endl;
            for (auto frame = 0 ; frame < inputHeader.frameCount ; frame++) {
                input.seekg(inputHeader.offsetToData + (frame * inputHeader.frameLength) + chunk.oldIndex , std::ios::beg) ;
                output.seekp(inputHeader.offsetToData + (frame * outHeader.frameLength) + chunk.newIndex, std::ios::beg) ;
                input.read(buffer.data(), buffer.size());
                output.write(buffer.data(),buffer.size()) ;

            }
        }
        
        /*
        
        for ( auto frame = 0 ; frame < frameCount ; frame++) {
            for (const auto &chunk:entry.chunks) {
                auto buffer = std::vector<char>(chunk.length,0) ;
                if (oneShot){
                    std::cout << "\t\tProcessing chunk: " << chunk.label << std::endl;
                }
                input.seekg(DATAOFFSET + (frame * frameLength) + chunk.oldIndex , std::ios::beg) ;
                output.seekp(DATAOFFSET + (frame * outLength) + chunk.newIndex, std::ios::beg) ;
                input.read(buffer.data(), buffer.size());
                output.write(buffer.data(),buffer.size()) ;
            }
        }
         */
    }
}

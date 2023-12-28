//Copyright © 2023 Charles Kerr. All rights reserved.

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include "containers/lightfile/lightheader.hpp"

auto convert(const std::filesystem::path &inputfile, const std::filesystem::path outputlocation) -> void ;
int main(int argc, const char * argv[]) {
    if (argc != 3) {
        std::cerr <<"Insufficent parameters" << std::endl;
        std::cerr << "Usage: convertlight inputdirectory outputdirectory" << std::endl;
        return 1 ;
    }
    auto inputdir = std::filesystem::path(argv[1]) ;
    auto outdir = std::filesystem::path(argv[2]) ;
    
    for ( const auto &entry: std::filesystem::directory_iterator(inputdir)) {
        // check to ensure this extension is something we want
        if (entry.is_regular_file()) {
            if (entry.path().extension() == ".diybpb") {
                convert(entry.path(),outdir) ;
            }
        }
    }
    
    return 0;
}
//=========================================================================================================
auto convert(const std::filesystem::path &inputfile, const std::filesystem::path outputlocation) -> void {
    try {
        auto input = std::ifstream(inputfile.string(),std::ios::binary) ;
        if (!input.is_open()) {
            std::cerr << "Unable to open: " << inputfile.string() ;
            return ;
        }
        // Buld the output file  path
        auto outputname = outputlocation / ((inputfile.stem()).replace_extension(".light")) ;
        
        std::cout << "input:  " << inputfile.string() << std::endl ;
        std::cout << "output: " << outputname.string() << std::endl;
        auto output = std::ofstream(outputname.string(),std::ios::binary) ;
        if (!output.is_open()){
            std::cerr << "Unable to open: " << outputname.string() << std::endl;
            return ;
        }
        
        auto oldheader = LightHeader(input) ;
        auto header = LightHeader() ;
        header.frameCount = oldheader.frameCount ;
        header.frameLength = oldheader.frameLength ;
        
        header.sampleRate = oldheader.sampleRate  ;
        header.sourceName = inputfile.stem().string() ;
        header.write(output) ;
        // now we just read/write
        char data ;
        while (input.good() && !input.eof()) {
            input.read(&data,1) ;
            if (input.gcount() == 1){
                output.write(&data, 1) ;
            }
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

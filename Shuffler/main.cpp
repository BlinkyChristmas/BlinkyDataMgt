//Copyright © 2023 Charles Kerr. All rights reserved.

#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <fstream>

#include "sourcecollection.hpp"
#include "inputlist.hpp"
#include "containers/lightfile/lightheader.hpp"

using namespace std::string_literals ;

auto showUsage() -> void;
auto makeEmptyLightFile(const std::filesystem::path &outPath, int frameCount, int frameLength) -> void ;


//===========================================================================================================
//
int main(int argc, const char * argv[]) {
    auto status = EXIT_SUCCESS ;
    try {
        if (argc != 4 ) {
            status = EXIT_FAILURE ;
            showUsage() ;
        }
        else {
            auto configpath = std::filesystem::path(argv[1]) ;
            auto inputpath = std::filesystem::path(argv[2]) ;
            auto outputpath = std::filesystem::path(argv[3]) ;
            auto sourceCollection = SourceCollection(configpath) ;
            auto inputList = InputList(inputpath) ;
            for (const auto &lightdata:inputList.inputs) {
                // Get the frame length
                auto outLength = sourceCollection.frameLength() ;
                auto frameCount = sourceCollection.frameCount(lightdata) ;
                std::cout << "Processing: " << lightdata.string()<<" #Frames: "<<frameCount << " #Channels: "<<outLength<<std::endl;
                // Make the blank output file
                makeEmptyLightFile(outputpath/lightdata, frameCount, outLength) ;
                // Now open the file we just created, read and write
                auto output = std::fstream((outputpath/lightdata).string(),std::ios::in | std::ios::out | std::ios::binary) ;
                if (!output.is_open()){
                    throw (std::runtime_error("Unable to reopen output file: "s + (outputpath/lightdata).string()));
                }
                sourceCollection.processFor(lightdata, output) ;
            }
        }
    }
    catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
        status = EXIT_FAILURE ;
    }
    catch(...) {
        std::cerr <<"Unknown error\n" ;
        status = EXIT_FAILURE ;
    }
    return status ;
}

//===========================================================================================================
auto showUsage() -> void {
    std::cout << "Usage: \n";
    std::cout << "      binaryshuffle configpath inputlist outputpath \n";
    std::cout << "Where:\n";
    std::cout << "                configpath - the full/relative path to the configuration file\n";
    std::cout << "                inputlist  - the full/relative list to the input files to process\n" ;
    std::cout << "                outputpath - the output path (directory) to place the outputs \n" ;
}

//============================================================================================================
auto makeEmptyLightFile(const std::filesystem::path &outPath, int frameCount, int frameLength) -> void {
    
    auto buffer = std::vector<char>(frameLength,0) ;
    auto output = std::ofstream(outPath.string(),std::ios::binary) ;
    if (!output.is_open()) {
        throw std::runtime_error("Unable to create: "s + outPath.string());
    }
    LightHeader header ;
    header.frameCount = frameCount ;
    header.frameLength = frameLength ;
    header.write(output) ;
    for (auto frame = 0 ; frame < frameCount ; frame++){
        output.write(buffer.data(),buffer.size()) ;
    }
}

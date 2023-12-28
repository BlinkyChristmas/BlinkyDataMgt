//Copyright © 2023 Charles Kerr. All rights reserved.

#include <iostream>
#include <filesystem>

#include "containers/wavfile/mwavfile.hpp"
#include "containers/lightfile/lightfile.hpp"
int main(int argc, const char * argv[]) {
    
    if (argc != 2) {
        std::cerr <<"File path is not specified"<<std::endl;
        return 1 ;
    }
    // We will go by extension, for file type
    auto path = std::filesystem::path(argv[1]) ;
    if (!std::filesystem::exists(path)){
        std::cerr <<"Unable to locate: "<<path.string()<<std::endl;
        return 1 ;
    }
    auto extension = path.extension().string() ;
    if (extension == ".light"){
        try {
            LightFile light ;
            if (!light.loadFile(path)) {
                std::cerr <<"Error loading: "<< path.string()<<std::endl;
                return 1;
            }
            std::cout << "Frame count: "<<light.frameCount() << std::endl;
        }
        catch(const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return 1 ;
        }
    }
    else if (extension == ".wav"){
        MWAVFile wave;
        try {
            if (!wave.load(path)){
                std::cerr <<"Error loading: "<< path.string()<<std::endl;
                return 1;
 
            }
            std::cout << "Frame count: "<<wave.frameCount() << std::endl;
        }
        catch(const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return 1 ;
        }
    }
    else {
        std::cerr << "Unknown file type: "<< extension<<std::endl;
        return 1 ;
    }
    return 0;
}

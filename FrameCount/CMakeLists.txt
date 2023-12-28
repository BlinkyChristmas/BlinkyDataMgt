# ************************************************************************************
# How to build
#
# From the top level directory of the project
#
# cmake . -B ./build -DCMAKE_BUILD_TYPE=Release
# cmake --build ./build --config Release
#
# *************************************************************************************



cmake_minimum_required(VERSION 3.24)
project(FrameCount VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# ***********************************************************************
# The executable we are making
# ***********************************************************************
add_executable(FrameCount
    ${PROJECT_SOURCE_DIR}/main.cpp

    ${PROJECT_SOURCE_DIR}/../containers/lightfile/lightfile.cpp
    ${PROJECT_SOURCE_DIR}/../containers/lightfile/lightfile.hpp
    ${PROJECT_SOURCE_DIR}/../containers/lightfile/lightheader.cpp
    ${PROJECT_SOURCE_DIR}/../containers/lightfile/lightheader.hpp

    ${PROJECT_SOURCE_DIR}/../containers/wavfile/chunkheader.cpp
    ${PROJECT_SOURCE_DIR}/../containers/wavfile/chunkheader.hpp
    ${PROJECT_SOURCE_DIR}/../containers/wavfile/fileheader.cpp
    ${PROJECT_SOURCE_DIR}/../containers/wavfile/fileheader.hpp
    ${PROJECT_SOURCE_DIR}/../containers/wavfile/mwavfile.cpp
    ${PROJECT_SOURCE_DIR}/../containers/wavfile/mwavfile.hpp
    ${PROJECT_SOURCE_DIR}/../containers/wavfile/wavfmtchunk.cpp
    ${PROJECT_SOURCE_DIR}/../containers/wavfile/wavfmtchunk.hpp

    
    ${PROJECT_SOURCE_DIR}/../utility/strutil.hpp
    ${PROJECT_SOURCE_DIR}/../utility/mapfile.cpp
    ${PROJECT_SOURCE_DIR}/../utility/mapfile.hpp
)
    
# ***********************************************************************
# The include paths
# ***********************************************************************
target_include_directories(FrameCount
    PUBLIC
        ${PROJECT_SOURCE_DIR}/
        ${PROJECT_SOURCE_DIR}/../
)
# ***********************************************************************
# Compilier switches/defines
# ***********************************************************************

target_compile_definitions(FrameCount PRIVATE
    $<$<PLATFORM_ID:Windows>:_CONSOLE>
    $<$<CONFIG:Release>:NDEBUG>
    $<$<CONFIG:Debug>:_DEBUG>
)

if(WIN32)
target_compile_options(FrameCount PRIVATE
    $<$<CONFIG:Release>:/O2>
)
else()
target_compile_options(FrameCount PRIVATE
    $<$<CONFIG:Release>:-O2>
)
endif(WIN32)

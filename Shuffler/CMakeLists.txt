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
project(Shuffler VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# ***********************************************************************
# The executable we are making
# ***********************************************************************
add_executable(Shuffler
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/chunk.cpp
    ${PROJECT_SOURCE_DIR}/chunk.hpp
    ${PROJECT_SOURCE_DIR}/inputlist.cpp
    ${PROJECT_SOURCE_DIR}/inputlist.hpp
    ${PROJECT_SOURCE_DIR}/sourcecollection.cpp
    ${PROJECT_SOURCE_DIR}/sourcecollection.hpp
    ${PROJECT_SOURCE_DIR}/sourcesection.cpp
    ${PROJECT_SOURCE_DIR}/sourcesection.hpp

    
    ${PROJECT_SOURCE_DIR}/../utility/strutil.hpp
    ${PROJECT_SOURCE_DIR}/../containers/lightfile/lightheader.hpp
    ${PROJECT_SOURCE_DIR}/../containers/lightfile/lightheader.cpp
)
    
# ***********************************************************************
# The include paths
# ***********************************************************************
target_include_directories(Shuffler
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/../
)
# ***********************************************************************
# Compilier switches/defines
# ***********************************************************************

target_compile_definitions(Shuffler PRIVATE
    $<$<PLATFORM_ID:Windows>:_CONSOLE>
    $<$<CONFIG:Release>:NDEBUG>
    $<$<CONFIG:Debug>:_DEBUG>
)

if(WIN32)
target_compile_options(Shuffler PRIVATE
    $<$<CONFIG:Release>:/O2>
)
else()
target_compile_options(Shuffler PRIVATE
    $<$<CONFIG:Release>:-O2>
)
endif(WIN32)

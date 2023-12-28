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
    ${PROJECT_SOURCE_DIR}/Shuffler/main.cpp
    ${PROJECT_SOURCE_DIR}/Shuffler/chunk.cpp
    ${PROJECT_SOURCE_DIR}/Shuffler/chunk.hpp
    ${PROJECT_SOURCE_DIR}/Shuffler/inputlist.cpp
    ${PROJECT_SOURCE_DIR}/Shuffler/inputlist.hpp
    ${PROJECT_SOURCE_DIR}/Shuffler/sourcecollection.cpp
    ${PROJECT_SOURCE_DIR}/Shuffler/sourcecollection.hpp
    ${PROJECT_SOURCE_DIR}/Shuffler/sourceselection.cpp
    ${PROJECT_SOURCE_DIR}/Shuffler/sourceselection.hpp

    
    ${PROJECT_SOURCE_DIR}/utility/strutil.hpp
    ${PROJECT_SOURCE_DIR}/containers/lightfile/lightheader.hpp
    ${PROJECT_SOURCE_DIR}/containers/lightfile/lightheader.cpp
)
    
# ***********************************************************************
# The include paths
# ***********************************************************************
target_include_directories(Shuffler
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/Shuffler
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

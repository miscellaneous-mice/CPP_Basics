cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(sstream VERSION 1.0) # Just to give the version to a project

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp) # To include all the cpp files from src/ to be compiled as part of executable via make

add_executable(executable main.cpp ${SRC_FILES}) # All the cpp files to compile using make to a executable

target_include_directories(executable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # to include the header files from here

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/exec) # Add a directory

# Put executables inside exec/
set_target_properties(executable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/exec"
)
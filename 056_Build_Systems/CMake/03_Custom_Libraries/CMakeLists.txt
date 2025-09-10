cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(sstream VERSION 1.0) # Just to give the version to a project

add_subdirectory(lib) # Include the CMakeLists.txt from lib/ folder

add_executable(hashing_exec main.cpp) # All the cpp files to compile using make to a executable
target_link_libraries(hashing_exec PUBLIC mylib) # link the libraries to the executable

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/exec) # Add a directory

# Put executables inside exec/
set_target_properties(hashing_exec PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/exec"
)
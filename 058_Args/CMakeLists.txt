cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(args VERSION 1.0) # Just to give the version to a project

add_executable(exec main.cpp) # All the cpp files to compile using make to a executable\

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/exec) # Add a directory

# Put executables inside exec/
set_target_properties(exec PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/exec"
)
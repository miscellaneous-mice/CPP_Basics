cmake_minimum_required(VERSION 3.10)

# Use C standard instead of C++
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(distributions VERSION 1.0 LANGUAGES C)

# Build main.c into an executable
add_executable(executable main.c)

# Add include directory
target_include_directories(executable PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Create a custom output directory for the executable
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/exec)

set_target_properties(executable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/exec"
)

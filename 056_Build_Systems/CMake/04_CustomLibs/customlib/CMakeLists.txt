# Collect source files
file(GLOB_RECURSE LIB_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Build a shared library (creates libsstreamlib.dylib)
add_library(sstreamlib SHARED ${LIB_FILES})

# Add include directories (so headers are visible when linking this library)
target_include_directories(sstreamlib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
# Collect sources
file(GLOB_RECURSE LIB_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(mylib STATIC ${LIB_FILES})

# Add your project includes
target_include_directories(mylib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Link headers + libraries
target_include_directories(mylib PUBLIC ${OPENSSL_INCLUDE_DIR})

# target_link_libraries(mylib PUBLIC OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(mylib PUBLIC ${OPENSSL_LIBRARIES} ${OPENSSL_DEPENDENCIES})
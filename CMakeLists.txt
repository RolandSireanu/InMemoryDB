cmake_minimum_required(VERSION 3.11)  # Ensure you have at least CMake 3.11
project(InMemoryDB)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include also *.cc files in SOURCE
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.cc")
file(GLOB_RECURSE CLIENT_SOURCES "client/*.cpp")
set (SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/include/format.pb.cc)
set (CLIENT_SOURCES ${CLIENT_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/include/format.pb.cc)


include(FetchContent)

# Fetch Boost
FetchContent_Declare(
    boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG        boost-1.86.0  # Use the latest version or a specific one
)

# Fetch Protocol Buffers
FetchContent_Declare(
    protobuf
    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
    GIT_TAG        main  # Use the latest stable version or a specific one
)

# Make sure to fetch the contents
FetchContent_MakeAvailable(boost protobuf)

add_custom_target(build_protocol
    COMMAND ${protobuf_BINARY_DIR}/protoc --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/include  --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/include format.proto
)

# Your executable or library
add_executable(${PROJECT_NAME} ${SOURCES})  # Replace with your source file
add_dependencies(build_protocol protoc)
add_dependencies(${PROJECT_NAME} build_protocol)

add_executable(client ${CLIENT_SOURCES})


# Link against the necessary libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Boost::asio             # Linking Boost.Asio
    protobuf::libprotobuf   # Linking Protocol Buffers
    ${Protobuf_LIBRARIES}
)

target_link_libraries(client
    PRIVATE
    Boost::asio             # Linking Boost.Asio
    protobuf::libprotobuf   # Linking Protocol Buffers
    ${Protobuf_LIBRARIES}
)

# Ensure to find and link Boost dependencies
# find_package(Boost REQUIRED COMPONENTS asio system)  # Find Boost.Asio

# Add include directories for Boost
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

# Add include directories for Boost
target_include_directories(client
    PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)
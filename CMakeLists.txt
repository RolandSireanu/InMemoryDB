cmake_minimum_required(VERSION 3.11)  # Ensure you have at least CMake 3.11
project(InMemoryDB)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")

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
    GIT_TAG        v21.12  # Use the latest stable version or a specific one
)

# Make sure to fetch the contents
FetchContent_MakeAvailable(boost protobuf)

# Your executable or library
add_executable(${PROJECT_NAME} ${SOURCES})  # Replace with your source file

# Link against the necessary libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Boost::asio             # Linking Boost.Asio
    protobuf::libprotobuf   # Linking Protocol Buffers
)

# Ensure to find and link Boost dependencies
# find_package(Boost REQUIRED COMPONENTS asio system)  # Find Boost.Asio

# Add include directories for Boost
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${Boost_INCLUDE_DIRS}
)
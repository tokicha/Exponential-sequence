cmake_minimum_required(VERSION 3.14)
project(exponential_engine_api CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find system Asio package installed by Dockerfile
find_package(Asio REQUIRED)

# Include Crow header-only file (or FetchContent if using git)
include(FetchContent)
FetchContent_Declare(
    crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG v1.0+5
)
FetchContent_MakeAvailable(crow)

# Build the executable
add_executable(exponential_engine_api main.cpp)
target_link_libraries(exponential_engine_api PRIVATE crow::crow Asio::Asio)


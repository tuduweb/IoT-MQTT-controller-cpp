set(CMAKE_CXX_STANDARD 11)

cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0048 NEW)

project(remoteControl)

#set(CMAKE_INCLUDE_PATH "/usr/local/include/")

#include(./3rdparty/cxxopts/cmake/cxxopts.cmake)

include_directories(./3rdparty/cxxopts/include/)

add_executable(remoteControl
    ./src/main.cpp
    ./src/CommonTools.cpp
    ./src/CommonTools.hpp
    ./src/IoTPlaform.cpp
    ./src/IoTPlaform.hpp
    ./3rdparty/cxxopts/include/cxxopts.hpp
    ./src/config.hpp
)

# set(LIB_TYPE STATIC)
# set(TARGET_OUTPUT_NAME_PREFIX "tencentcloud-sdk-cpp-" CACHE STRING "The target's output name prefix")

# add_subdirectory(3rdparty/tencentcloud-sdk-cpp/core)
# add_subdirectory(3rdparty/tencentcloud-sdk-cpp/iotexplorer)

#add_library(tencentcloud-sdk-cpp-core STATIC) 

#find_library()

#include(cloud.cmake)

target_link_libraries(remoteControl tencentcloud-sdk-cpp-iotexplorer.a tencentcloud-sdk-cpp-core.a  -lpthread  -lcurl -lcrypto -luuid)

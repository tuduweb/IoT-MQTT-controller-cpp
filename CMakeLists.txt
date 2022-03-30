project(remoteControl)

set(CMAKE_CXX_STANDARD 11)

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
)

target_link_libraries(remoteControl tencentcloud-sdk-cpp-core tencentcloud-sdk-cpp-iotexplorer -lcurl)

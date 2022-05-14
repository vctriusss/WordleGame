cmake_minimum_required(VERSION 3.21)
project(WordleGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(WordleGame Game/main.cpp Game/Cell.cpp)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS graphics window system REQUIRED)
#include(FetchContent)
#FetchContent_Declare(
#        spdlog
#        GIT_REPOSITORY https://github.com/gabime/spdlog.git
#        GIT_TAG        v1.10.0 # release-1.10.0
#)
#FetchContent_MakeAvailable(spdlog)

include_directories(С:/SFML-2.5.1/include)
target_link_libraries(WordleGame sfml-system sfml-window sfml-graphics)


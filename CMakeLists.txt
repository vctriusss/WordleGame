cmake_minimum_required(VERSION 3.21)
project(WordleGame)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(external/doctest)
add_executable(game_test Game/functions.hpp Game/test.cpp)
target_link_libraries(game_test doctest)
add_test(NAME test COMMAND test --force-colors -d)
add_custom_target(cloud-test COMMAND test --force-colors -d)

add_executable(WordleGame Game/main.cpp Game/Cell.cpp Game/Game.cpp Game/functions.cpp)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS graphics window system REQUIRED)

include_directories(С:/SFML-2.5.1/include)
target_link_libraries(WordleGame sfml-system sfml-window sfml-graphics)


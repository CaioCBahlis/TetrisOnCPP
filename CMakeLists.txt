cmake_minimum_required(VERSION 3.26)
project(untitled5)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
fetchcontent_declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)



set(CMAKE_CXX_STANDARD 17)

add_executable(untitled5 main.cpp)

target_link_libraries(untitled5 sfml-graphics)
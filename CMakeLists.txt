cmake_minimum_required(VERSION 3.16)
project(MonteCarloPi)
set(CMAKE_CXX_STANDARD 17)

find_package(SFML COMPONENTS graphics audio REQUIRED)
file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*.c* ${PROJECT_SOURCE_DIR}/src/*.h*)
add_executable(MonteCarloPi ${SRC})

target_link_libraries(MonteCarloPi sfml-graphics)

cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(platonic_solids)

find_package(SDL3 REQUIRED)

include_directories(include)

add_executable(
    ${PROJECT_NAME}
    source/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
